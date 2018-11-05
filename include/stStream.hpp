/*

Base class for file stream and stream helper.  Provides file writing and reading methods.

*/

#ifndef __STLIB_STREAM_H__
#define __STLIB_STREAM_H__

#include <stdio.h>
#include "_stdefs.h"

namespace_stLib {


/***********************************************************************

	File open modes

***********************************************************************/
enum ST_FILEOPENMODE : n8 {
	ST_NOMODE				= 0,
	// Binary
	ST_WRITE_BINARY			= 1,
	ST_READ_BINARY			= 2,
	ST_CREATE_BINARY		= 3,
	// ASCI
	ST_WRITE_ASCI			= 7,
	ST_READ_ASCI			= 8,
	ST_CREATE_ASCI			= 9,
	// Unicode
	ST_WRITE_UNICODE		= 4,
	ST_READ_UNICODE			= 5,
	ST_CREATE_UNICODE		= 6,
	// UTF-8
	ST_WRITE_UTF8			= 10,
	ST_READ_UTF8			= 11,
	ST_CREATE_UTF8			= 12
};

/***********************************************************************

	File positions

***********************************************************************/
enum ST_FILEPOSITIONORG : n8 {
	ST_CUR					= SEEK_CUR,
	ST_END					= SEEK_END,
	ST_HEAD					= SEEK_SET
};

enum STERR_STREAMERRS {
	ST_ERR_UNKNOWNOPENMODE 		= -11,
	ST_ERR_NULLFILEHANDLE 		= -12,
	ST_ERR_CREATECLONEFILE      = -13,
	ST_ERR_CLOSECLONEFILE		= -14,
	ST_ERR_OPENFILEHANDLE 		= -15,
	ST_ERR_OPENEDFILEHANDLE 	= -16,
	ST_ERR_CLOSEFILE 			= -17,
	ST_ERR_SEEK 				= -18,
	ST_ERR_FLUSHFILE 			= -19,
	ST_ERR_OUTOFSIZE 			= -20,
	ST_ERR_NULLDATAPARAM 		= -21,
	ST_ERR_UNABLEWRITE 			= -22,
	ST_ERR_UNABLEREAD 			= -23,
	ST_ERR_NULLSTREAMHANDLE 	= -24,
	ST_ERR_READBYTE 			= -25,
	ST_ERR_WRITEBYTE 			= -26,
	ST_ERR_READTEXT 			= -27,
	ST_ERR_WRITETEXT 			= -28
}; 

template<typename type_of_char>
ST_INLINE FILE* st_fopen( type_of_char const* _FileName, type_of_char const* _Mode);
template<> ST_INLINE FILE* st_fopen( char const* _FileName, char const* _Mode) { return fopen( _FileName, _Mode ); }
template<> ST_INLINE FILE* st_fopen( wchar_t const* _FileName, wchar_t const* _Mode) { return _wfopen( _FileName, _Mode ); }

/***********************************************************************

  Stream

***********************************************************************/
template<typename type_stStr>
class stStream {
protected:
	ST_FILEOPENMODE			m_mode;		
	FILE *                  m_pfile;	
	un32					m_size;		
	bool					m_isOpen;	

public:
	stResult Open( const type_stStr &path, const ST_FILEOPENMODE mode ) {
		if( m_pfile ) {
			return ST_ERR_OPENFILEHANDLE;
		}
		switch( mode ) {
			// Unicode mode
		case ST_WRITE_UNICODE:
		m_pfile = st_fopen<type_stStr::char_type>( path.Raw(), L"rt+,ccs=UNICODE" );
		break;
		case ST_READ_UNICODE:
		m_pfile = st_fopen<type_stStr::char_type>( path.Raw(), L"rt,ccs=UNICODE" );
		break;
		case ST_CREATE_UNICODE:
		m_pfile = st_fopen<type_stStr::char_type>( path.Raw(), L"wt+,ccs=UNICODE" );
		break;
		// UTF-8
		case ST_WRITE_UTF8:
		m_pfile = st_fopen<type_stStr::char_type>( path.Raw(), L"rt+,ccs=UTF-8" );
		break;
		case ST_READ_UTF8:
		m_pfile = st_fopen<type_stStr::char_type>( path.Raw(), L"rt,ccs=UTF-8" );
		break;
		case ST_CREATE_UTF8:
		m_pfile = st_fopen<type_stStr::char_type>( path.Raw(), L"wt+,ccs=UTF-8" );
		break;
		// ASCI
		case ST_WRITE_ASCI:
		m_pfile = st_fopen<type_stStr::char_type>( path.Raw(), L"rt+" );
		break;
		case ST_READ_ASCI:
		m_pfile = st_fopen<type_stStr::char_type>( path.Raw(), L"rt" );
		break;
		case ST_CREATE_ASCI:
		m_pfile = st_fopen<type_stStr::char_type>( path.Raw(), L"wt" );
		break;
		// Binary
		case ST_WRITE_BINARY:
		m_pfile = st_fopen<type_stStr::char_type>( path.Raw(), L"rb+" );
		break;
		case ST_READ_BINARY:
		m_pfile = st_fopen<type_stStr::char_type>( path.Raw(), L"rb" );
		break;
		case ST_CREATE_BINARY:
		m_pfile = st_fopen<type_stStr::char_type>( path.Raw(), L"wb" );
		break;
		}
		if( !m_pfile ) {
			return ST_ERR_OPENFILEHANDLE;
		}
		// get size of file
		Move( 0L, ST_END );
		m_size = Pos();
		MoveHead();

		m_isOpen = true;
		m_mode = mode;
	}

	stResult Close() {
		if( !m_pfile ) {
			return( ST_ERR_NULLFILEHANDLE );
		}
		if( EOF == fclose( m_pfile ) ) {
			return( ST_ERR_CLOSEFILE );
		}
		m_pfile = NULL;
		m_size = 0UL;
		m_mode = ST_NOMODE;
		m_isOpen = false;
		return( ST_NOERR );
	}
	stResult Move( const n32 pos, const ST_FILEPOSITIONORG org ){
		if ( 0 != fseek( m_pfile, pos, org ) ) {
			return( org );
		}
		return( ST_NOERR );
	}

	stResult MoveHead() {
		return Move( 0, ST_HEAD );
	}
	stResult SaveAs( const type_stStr &newPath ) {
		FILE   *pnew = _wfopen( newPath.Raw(), L"wb" );
		byte8  c = 0;
		const un32 orgPos = Pos();

		if( !pnew ) {
		}
		MoveHead();
		for( nbus i = 0; i < Size(); ++i ) {
			c = fgetc( m_pfile );
			fputc( c, pnew );
		}
		Save();
		if( EOF == fclose( pnew ) ) {
		}
		Move( orgPos, ST_HEAD );
	}

	stResult Save() {
		if( !m_pfile ) {
			return( ST_ERR_NULLFILEHANDLE );
		}
		if( fflush( m_pfile ) != 0 ) {
			return( ST_ERR_FLUSHFILE );
		}
		return( ST_NOERR );
	}
	un32					Size()		const { return m_size; }
	un32					Pos()		const { return ftell( m_pfile ); }
	bool					IsOpen()	const { return ( bool )m_isOpen; }
	bool					IsEOF()		const { return ( bool )feof( m_pfile ); }
	void *					Handle()	const { return m_pfile; }
	stLib::ST_FILEOPENMODE	Mode()		const { return m_mode; }

	stStream()
		: m_pfile( NULL ), m_isOpen( false ), m_mode( stLib::ST_NOMODE ), m_size( 0 ) { }
	virtual ~stStream() {
		Close();
	}
};
using stStreamA = stStream<stStrA>;
using stStreamW = stStream<stStrW>;

/***********************************************************************

  Stream helpers

***********************************************************************/
template<typename type_stStr>
class stStreamHelper {
protected:
	stLib::stStream<type_stStr>*m_pparent;

	stStreamHelper( const stStreamHelper & ) = delete;

	FILE *hfile() { return ( FILE * )m_pparent->Handle(); }
	stLib::stStream<type_stStr> *	hstream() { return m_pparent; }

public:
	stResult ReadBytes( const un32 counts, byte8 **ppdata ) {
		un32 size = counts;

		if( !hstream() ) {
			return( ST_ERR_NULLSTREAMHANDLE );
		}
		if( ST_READ_BINARY != hstream()->Mode() ) {
			return( ST_ERR_UNABLEREAD );
		}
		if( counts > hstream()->Size() ) {
			return( ST_ERR_OUTOFSIZE );
		} else if( !counts ) {
			size = hstream()->Size();
		}

		if( !fread( *ppRaw, sizeof( byte8 ), size, hfile() ) ) {
			return( ST_ERR_READBYTE );
		}
		return( ST_NOERR );
	}
	stResult WriteBytes( const un32 counts, byte8 *data ) {
		if ( ! hstream() ) {
			return( ST_ERR_NULLSTREAMHANDLE );
		}
		if ( ST_WRITE_BINARY != hstream()->Mode() ) {
			return( ST_ERR_UNABLEWRITE );
		}
		if ( counts > hstream()->Size() ) {
			return( ST_ERR_OUTOFSIZE );
		}
		if ( ! data ) {
			return( ST_ERR_NULLDATAPARAM );
		}
		if ( ! fwrite( data, sizeof( byte8 ), counts, hfile() ) ) {
			return( ST_ERR_WRITEBYTE );
		}
		return( ST_NOERR );
	}
	void					SetStream( stLib::stStream<type_stStr> *parent )  { m_pparent = parent; }
	void					DeleteStream() { st_safe_del( m_pparent ); }
	stLib::stStream<type_stStr> *	GetStream() const { return m_pparent; }

	stStreamHelper( stLib::stStream<type_stStr> *pparent )
		: m_pparent( pParent ) { }
	stStreamHelper()
		: m_pparent( NULL ) { }
	virtual					~stStreamHelper() { }
};
using stStreamHelperA = stStreamHelper<stStrA>;
using stStreamHelperW = stStreamHelper<stStrW>;

}

#endif /* !__STLIB_STREAM_H__ */
