#include <malloc.h>
#include "..\utils\Maths.h"
#include "ErrCode.h"
#include "Core.h"
#include "MemPool.h"

using namespace stLibErrCode;

/*
============
MovNext
============
*/
ST_INLINE void *MovNext( void *pmem, const un64 size ) {
	return ( byte8 * )pmem + ( size / sizeof ( byte8 ) );
}

/*
============
MovBack
============
*/
ST_INLINE void *MovBack( void *pmem, const un64 size ) {
    return ( byte8 * )pmem - ( size / sizeof ( byte8 ) );
}

/*
==============================================================

	Memory pieces

==============================================================
*/

/*
============
stMemPiece::Merge
============
*/
stMemPiece stMemPiece::Merge( const stMemPiece &piece1, const stMemPiece &piece2 ) {
	void *phead    = ST_MAX( piece1.Head(), piece2.Head() );
	un64 mergeSize = piece1.Size() + piece2.Size();

	return stMemPiece( phead, mergeSize );
}

/*
============
stMemPiece::Split
============
*/
stMemPiece stMemPiece::Split( stMemPiece &piece1, const un64 piece1Size ) {
	stMemPiece newPiece( MovNext( piece1.Head(), piece1Size + 1), piece1.Size() - piece1Size );

	piece1.Resize( piece1Size );
	return newPiece;
}

/*
============
stMemPiece::stMemPiece
============
*/
stMemPiece::stMemPiece( void *phead, const un64 pieceSize )
	: m_phead( phead ), m_pend( MovNext( phead, pieceSize ) ), m_available( false ), m_size( pieceSize ) {

}

stMemPiece::stMemPiece( const stMemPiece &cpy ) : m_phead( NULL ) {
    if ( this != &cpy ) {
        memcpy( this, &cpy, sizeof( stMemPiece ) );
    }
}

/*
============
stMemPiece::~stMemPiece
============
*/
stMemPiece::~stMemPiece() { }

/*
============
stMemPiece::Refund
============
*/
stMemPiece &stMemPiece::Refund() {
	m_available = false;
	return *this;
}

/*
============
stMemPiece::Take
============
*/
stMemPiece &stMemPiece::Take() {
	m_available = true;
	return *this;
}

/*
============
stMemPiece::Clear
============
*/
stMemPiece &stMemPiece::Clear() {
	st_zero_memory( m_phead, m_size );
	return *this;
}

/*
============
stMemPiece::Resize
============
*/
stMemPiece &stMemPiece::Resize( const un64 newSize ) {
	m_pend = MovNext( m_phead, newSize );
	return *this;
}

/*
==============================================================

	Memory cake

==============================================================
*/

/*
============
stMemCake::stMemCake
============
*/
stMemCake::stMemCake( const un64 cakeSize )
	: m_size( cakeSize ) {
	m_phead 	  = malloc( cakeSize );
	st_zero_memory( m_phead, cakeSize );
	m_pcurSection = m_phead;
	m_pend        = MovNext( m_phead, cakeSize ) ;
}

/*
============
stMemCake::~stMemCake
============
*/
stMemCake::~stMemCake() { }

/*
============
stMemCake::mergePieces
============
*/
stMemPiece &stMemCake::mergePieces( const nbus srcIndex, const un32 counts ) {
	stMemPiece *phead = &m_pieces[srcIndex];

	for ( un32 i = 0; i < counts - 1; ++i ) {
		phead->Resize( stMemPiece::Merge( *phead, m_pieces[srcIndex + i + 1] ).Size() );
		m_pieces.erase( m_pieces.begin() + srcIndex + i + 1  );
	}
	return *phead;
}

/*
============
stMemCake::splitPiece
============
*/
stMemPiece &stMemCake::splitPiece( const nbus srcIndex, const un64 prevSize ) {
	stMemPiece fontPiece( stMemPiece::Split( m_pieces[srcIndex], prevSize ) );

	m_pieces.insert( m_pieces.begin() + srcIndex, fontPiece );
	return m_pieces[srcIndex + 1];
}

/*
============
stMemCake::GetRestMax
============
*/
un64 stMemCake::GetRestMax() {
	un64 refundedMax   = 0;
	un64 piecesSize    = 0;

	for ( nbus i = 0; i < m_pieces.size(); ++i ) {
		if ( ! m_pieces[i].Available() ) {
			refundedMax = ST_MAX( m_pieces[i].Size(), refundedMax );
		}
		piecesSize += m_pieces[i].Size();
	}
	return ST_MAX( ( m_size - piecesSize ), refundedMax );
}

/*
============
stMemCake::UseRefunded
============
*/
void *stMemCake::UseRefunded( const un64 neededSize ) {
    stMemPiece *piece   = NULL;

	for ( nbus i = 0; i < m_pieces.size(); ++i ) {
		piece = &m_pieces[i];

		if ( piece->Available() ) {
			if ( neededSize <= piece->Size() ) {
				if ( neededSize < ( piece->Size() / 2 ) ) {
					// current piece is too big
					return splitPiece( i, neededSize ).Take().Head();
				} else {
					return piece->Take().Head();
				}
			}
        }
	}
	return NULL;
}

/*
============
stMemCake::Section
============
*/
void *stMemCake::Section( const un64 size ) {
	void *pafterSection = MovNext( m_pcurSection, size );

	if ( pafterSection <= m_pend ) {
		stMemPiece piece( m_pcurSection, size );

		m_pcurSection = pafterSection;
		m_pieces.push_back( piece.Take() );
		return piece.Head();
	}
	return NULL;
}

/*
============
stMemCake::Refund
============
*/
bool stMemCake::Refund( const void *phead ) {
	for ( nbus i = 0; i < m_pieces.size(); ++i ) {
		if ( m_pieces[i].Head() == phead ) {
			m_pieces[i].Refund().Clear();
			return true;
		}
	}
	return false;
}

/*
==============================================================

	Memory pool

==============================================================
*/

/*
============
stMemPool::stMemPool
============
*/
stMemPool::stMemPool( const un64 eachCakeSize ) : m_cakeSize( eachCakeSize ) {
	stMemCake cake( m_cakeSize );
	m_cakes.push_back( cake );
}

/*
============
stMemPool::Alloc
============
*/
void *stMemPool::Alloc( const un64 size ) {
	// big memory
	if ( size >= m_cakeSize ) {
		void * ptr = malloc( size );
		m_bigMems.push_back( ptr );
		return ptr;
	}
	// last cake does not have enough space
    if ( size > m_cakes[m_cakes.size() - 1].GetRestMax() ) {
        stMemCake cake( m_cakeSize );
        m_cakes.push_back( cake );
    }
    void *pmem = m_cakes[m_cakes.size() - 1].Section( size - 1 );
    if ( pmem ) {
        return pmem;
    }
    // try use previous cakes' refunded space
	for ( nbus i = 0; i < m_cakes.size() - 1; ++i ) {
		void * pmem = m_cakes[i].UseRefunded( size );
		if ( pmem != NULL ) {
            return pmem;
		}
	}
    st_core_return_with_var( ST_ERR_UNKNOWN, NULL );
}

/*
============
stMemPool::Free
============
*/
void stMemPool::Free( void *pmem ) {
    for ( nbus i = 0; i < m_bigMems.size(); ++i ) {
		if ( m_bigMems[i] == pmem ) {
			free( pmem );
			m_bigMems.erase( m_bigMems.begin() + i );
			return;
		}
	}
	for ( nbus i = 0; i < m_cakes.size(); ++i ) {
		if( true == m_cakes[i].Refund( pmem ) ) {
			return;
		}
    }
	st_core_return( ST_ERR_FREEANONBELONGNINGMEM );
}

