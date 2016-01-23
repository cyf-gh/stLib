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
stMemCake::~stMemCake() {
	free( m_phead );
}

/*
============
stMemCake::mergePieces
============
*/
stMemPiece &stMemCake::mergePieces( PieceIterator &headPiece, const un32 mergeCounts ) {
	for ( un32 i = 0; i < mergeCounts - 1; ++i ) {
		headPiece->Resize( stMemPiece::Merge( *headPiece, *( headPiece + 1 ) ).Size() );
		m_pieces.erase( headPiece + 1 );
	}
	return *headPiece;
}

/*
============
stMemCake::splitPiece
============
*/
stMemPiece &stMemCake::splitPiece( PieceIterator &bigPiece, un64 neededSize ) {
	stMemPiece fontPiece( stMemPiece::Split( *bigPiece, neededSize ) );

	m_pieces.insert( bigPiece + 1, fontPiece );
	return *bigPiece;
}

/*
============
stMemCake::GetRestMax
============
*/
un64 stMemCake::GetRestMax() {
	un64 refundedMax = 0;
	un64 piecesSize  = 0;

	for ( PieceIterator piece = m_pieces.begin(); piece != m_pieces.end(); ++piece ) {
		if ( ! piece->Available() ) {
			refundedMax = ST_MAX( piece->Size(), refundedMax );
		}
		piecesSize += piece->Size();
	}
	return ST_MAX( ( m_size - piecesSize ), refundedMax );
}

/*
============
stMemCake::UseRefunded
============
*/
void *stMemCake::UseRefunded( const un64 neededSize ) {
	un64 solidAvailSize = 0;
	un32 solidTimes		= 0;

	for ( PieceIterator piece = m_pieces.begin(); piece != m_pieces.end(); ++piece ) {
		if ( piece->Available() ) {
			if ( neededSize <= piece->Size() ) {
				if ( neededSize < ( piece->Size() / 2 ) ) {
					// current piece is too big
					return splitPiece( piece, neededSize ).Take().Head();
				} else {
					return piece->Take().Head();
				}
			} else {
				// calculate solid pieces
				solidAvailSize += piece->Size();
				++solidTimes;
			}

			if ( neededSize <= solidAvailSize ) {
                PieceIterator mergeHead = piece - solidTimes + 1;
				// merge fractional pieces
				return mergePieces( mergeHead, solidTimes ).Take().Head();
			}
		} else {
			// solid pieces interrupted
			solidAvailSize = 0;
			solidTimes = 0;
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
		m_pieces.push_back( piece );
		return piece.Take().Head();
	}
	return NULL;
}

/*
============
stMemCake::Refund
============
*/
bool stMemCake::Refund( const void *phead ) {
	for ( PieceIterator piece = m_pieces.begin(); piece != m_pieces.end(); ++piece ) {
		if ( piece->Head() == phead ) {
			piece->Refund().Clear();
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
	stMemCake *pcake = new stMemCake( m_cakeSize );
	m_cakes.push_back( *pcake );
}

/*
============
stMemPool::Alloc
============
*/
void *stMemPool::Alloc( const un64 size ) {
	if ( size >= m_cakeSize ) {
		void * ptr = malloc( size );
		m_bigMems.push_back( ptr );
		return ptr;
	}
	for ( CakeIterator cake = m_cakes.begin(); cake != m_cakes.end(); ++cake ) {
		if ( size > cake->GetRestMax() ) {
			// current cakes all do not have enough space
			stMemCake *pcake = new stMemCake( m_cakeSize );
			m_cakes.push_back( *pcake );
			continue;
		}
		void * pmem = cake->UseRefunded( size );
		return ( pmem != NULL ) ? pmem : cake->Section( size );
	}
	st_core_return_with_var( ST_ERR_UNKNOWN, NULL );
}

/*
============
stMemPool::Free
============
*/
void stMemPool::Free( void *pmem ) {
	for ( PtrIterator p = m_bigMems.begin(); p != m_bigMems.end(); ++p ) {
		if ( *p == pmem ) {
			free( pmem );
			m_bigMems.erase( p );
			return;
		}
	}
	for ( CakeIterator cake = m_cakes.begin(); cake != m_cakes.end(); ++cake ) {
		if( false == cake->Refund( pmem ) ) {
			continue;
		} else {
			return;
		}
	}
	st_core_return( ST_ERR_FREEANONBELONGNINGMEM );
}

