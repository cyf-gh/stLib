/*

Provides memory pool features.

*/
#ifndef __STLIB_MEMPOOL_H__
#define __STLIB_MEMPOOL_H__

#pragma message( "Target ERROR:[ stLib Memory pool has very low performance, do not use it any more! ]" )

#include <vector>
#include "Def.h"

#define                 ST_MEMPOOL_DEFAULT_CAKESIZE 1024

/***********************************************************************

    stMemPiece

***********************************************************************/

class stMemPiece {
private:
	void *      		m_phead;
	void *				m_pend;
	bool				m_available;
	un64				m_size;

public:
	static stMemPiece   Merge( const stMemPiece &piece1, const stMemPiece &piece2 );
	static stMemPiece   Split( stMemPiece &piece1, const un64 piece1Size );
	
public:
	void *       		Head() 		const { return m_phead; }
	void * 		 		End()  		const { return m_pend; }
    un64			    Size() 		const { return m_size; }
	bool				Available() const { return m_available; };

	stMemPiece &		Refund();
	stMemPiece &		Take();
	stMemPiece &		Clear();
	stMemPiece &		Resize( const un64 newSize );

						stMemPiece( void *phead, const un64 pieceSize );
						stMemPiece( const stMemPiece &cpy );
	virtual				~stMemPiece();
};

/***********************************************************************

    stMemCake

***********************************************************************/

class stMemCake {

	st_class_no_bin_cpy( stMemCake )

protected:
	typedef std::vector<stMemPiece> 		  Pieces;

	stMemPiece &		mergePieces( const nbus srcIndex, const un32 counts );
	stMemPiece & 		splitPiece( const nbus srcIndex, const un64 prevSize );

	Pieces				m_pieces;
	const un64 			m_size;
	void * 				m_phead;
	void * 				m_pend;
	void *				m_pcurSection;

public:
	un64 				GetRestMax();

	void *				UseRefunded( const un64 neededSize );
	void *				Section( const un64 size );

	bool				Refund( const void *phead );

                        stMemCake( const un64 cakeSize );
    virtual             ~stMemCake();
};

/***********************************************************************

    stMemPool

***********************************************************************/

class stMemPool {

	st_class_no_bin_cpy( stMemPool );

private:
						stMemPool( const un64 eachCakeSize );
						stMemPool( const stMemPool &cpy );

protected:
	typedef std::vector<stMemCake> 		        Cakes;
	typedef std::vector<void *>					Ptrs;

	const un64 			m_cakeSize;
	Cakes				m_cakes;
	Ptrs				m_bigMems;

public:
	static stMemPool &	Instance( const un64 eachCakeSize );

	void *				Alloc( const un64 size );
	void 				Free( void *pmem );
};

ST_INLINE stMemPool &stMemPool::Instance( const un64 eachCakeSize = ST_MEMPOOL_DEFAULT_CAKESIZE ) {
	static stMemPool instance( eachCakeSize );
	return instance;
}

#endif /* !__STLIB_MEMPOOL_H__ */
