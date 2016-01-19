#include "..\core\Core.h"
#include "..\core\ErrCode.h"
#include "Stream.h"
#include "..\base\Str.h"

using namespace stLibCore;
using namespace stLibErrCode;
using namespace stLibEnum;

/*
==============================================================

	stStream

==============================================================
*/

/*
============
stStream::stStream
============
*/
stStream::stStream()
	: m_pfile( NULL ), m_isOpen( false ), m_mode( stLibEnum::ST_NOMODE ), m_size( 0 )
{ }

/*
============
stStream::~stStream
============
*/
stStream::~stStream() {
	if ( m_isOpen ) {
		fclose( m_pfile );
	}
}

/*
============
stStream::Open
============
*/
void stStream::Open( const wchar_t *path, FILEOPENMODE mode ) {
	if ( m_pfile ) {
		st_core_return( ST_ERR_OPENEDFILEHANDLE );
	}
	switch ( mode ) {
		// Unicode mode
		case ST_WRITE_UNICODE :
			m_pfile = _wfopen( path, L"wt+,ccs=UNICODE" );
			break;
		case ST_READ_UNICODE :
			m_pfile = _wfopen( path, L"rt+,ccs=UNICODE" );
			break;
		case ST_CREATE_UNICODE :
			m_pfile = _wfopen( path, L"wt+,ccs=UNICODE" );
			break;
		// UTF-8
		case ST_WRITE_UTF8 :
			m_pfile = _wfopen( path, L"wt+,ccs=UTF-8" );
			break;
		case ST_READ_UTF8 :
			m_pfile = _wfopen( path, L"rt+,ccs=UTF-8" );
			break;
		case ST_CREATE_UTF8 :
			m_pfile = _wfopen( path, L"wt+,ccs=UTF-8" );
		// ASCI
		case ST_WRITE_ASCI :
			m_pfile = _wfopen( path, L"rt+" );
			break;
		case ST_READ_ASCI :
			m_pfile = _wfopen( path, L"rt" );
			break;
		case ST_CREATE_ASCI :
			m_pfile = _wfopen( path, L"wt" );
			break;
		// Binary
		case ST_WRITE_BINARY :
			m_pfile = _wfopen( path, L"rtb+" );
			break;
		case ST_READ_BINARY :
			m_pfile = _wfopen( path, L"rb" );
			break;
		case ST_CREATE_BINARY :
			m_pfile = _wfopen( path, L"wb" );
			break;
		default:
			st_core_return( ST_ERR_UNKNOWNOPENMODE );
	}
	if ( !m_pfile ) {
		st_core_return( ST_ERR_OPENFILEHANDLE );
	}
	// get size of file
	Move( 0, ST_END );
	m_size = GetPos();
	MoveHead();

	m_isOpen = true;
	m_mode = mode;
	st_core_return( ST_NOERR );
}

/*
============
stStream::Close
============
*/
void stStream::Close() {
	if ( ! m_pfile ) {
		st_core_return( ST_ERR_NULLFILEHANDLE );
	}
	if ( ! fclose( m_pfile ) ) {
		st_core_return( ST_ERR_CLOSEFILE );
	}
	m_pfile = NULL;
	m_size = 0UL;
	m_mode = ST_NOMODE;
	m_isOpen = false;
	st_core_return( ST_NOERR );
}

/*
============
stStream::Flush
============
*/
void stStream::Flush() {
	if ( ! m_pfile ) {
		st_core_return( ST_ERR_NULLFILEHANDLE );
	}
	if ( ! fflush( m_pfile ) ) {
		st_core_return( ST_ERR_FLUSHFILE );
	}
	st_core_return( ST_NOERR );
}

/*
============
stStream::MoveHead
============
*/
void stStream::MoveHead() {
	return Move( 0, ST_HEAD );
}

/*
============
stStream::Move
============
*/
void stStream::Move( const n32 pos, FILEPOSITIONORG org ){
	if ( ! fseek( m_pfile, pos, org  ) ) {
		st_core_return( ST_ERR_SEEK );
	}
	st_core_return( ST_NOERR );
}

/*
============
stStream::Move
============
*/
void stStream::Save( const wchar_t *newPath ) {
}

/*
==============================================================

	stStreamHelper

==============================================================
*/

/*
============
stStreamHelper::stStreamHelper
============
*/
stStreamHelper::stStreamHelper( stStream *pParent )
	: m_pParent( pParent ) { }

stStreamHelper::stStreamHelper()
	: m_pParent( NULL ) { }

/*
============
stStreamHelper::~stStreamHelper
============
*/
stStreamHelper::~stStreamHelper() { }

/*
==============================================================

	stStreamBinary

==============================================================
*/

/*
============
stStreamBinary::stStreamBinary
============
*/
stStreamBinary::stStreamBinary( stStream *parent )
	: stStreamHelper( parent ) { }

stStreamBinary::stStreamBinary()
	: stStreamHelper( NULL ) { }

/*
============
stStreamBinary::~stStreamBinary
============
*/
stStreamBinary::~stStreamBinary() {
	st_safe_del( m_pParent );
}

/*
============
stStreamBinary::ReadBytes
============
*/
void stStreamBinary::ReadBytes( const un32 counts, byte8 **ppdata ) {
	un32 kSize = counts;

	if ( ! hstream() ) {
		st_core_return( ST_ERR_NULLSTREAMHANDLE );
	}
	if ( ST_READ_BINARY != hstream()->GetMode() ) {
		st_core_return( ST_ERR_UNABLEREAD );
	}
	if ( counts > hstream()->GetSize() ) {
		st_core_return( ST_ERR_OUTOFSIZE );
	} else if ( ! counts ) {
		kSize = hstream()->GetSize();
	}

	* ppdata = new byte8[ kSize + 1 ];

	if( ! fread( * ppdata, 1, kSize , hfile() ) ) {
		st_core_return( ST_ERR_READBYTE );
	}
	st_core_return( ST_NOERR );
}

/*
============
stStreamBinary::WriteBytes
============
*/
void stStreamBinary::WriteBytes( const un32 counts, byte8 *data ) {
	if ( ! hstream() ) {
		st_core_return( ST_ERR_NULLSTREAMHANDLE );
	}
	if ( ST_WRITE_BINARY != hstream()->GetMode() ) {
		st_core_return( ST_ERR_UNABLEWRITE );
	}
	if ( counts > hstream()->GetSize() ) {
		st_core_return( ST_ERR_OUTOFSIZE );
	}
	if ( ! data ) {
		st_core_return( ST_ERR_NULLDATAPARAM );
	}
	if ( ! fwrite( data, sizeof( byte8 ), counts, hfile() ) ) {
		st_core_return( ST_ERR_WRITEBYTE );
	}
	st_core_return( ST_NOERR );
}

/*
==============================================================

	stStreamText

==============================================================
*/

/*
============
stStreamText::stStreamText
============
*/
stStreamText::stStreamText( stStream *parent  )
	: stStreamHelper( parent  ) { }

stStreamText::stStreamText()
	: stStreamHelper( NULL ) { }

/*
============
stStreamText::~stStreamText
============
*/
stStreamText::~stStreamText() {
	st_safe_del( m_pParent );
}

/*
============
stStreamText::ReadText
============
*/
void stStreamText::ReadText( const un32 counts, stStrW *str ) {
	un32 ulTextNumbersResult = counts;

	if ( ! hstream() )
		st_core_return( ST_ERR_NULLSTREAMHANDLE );
	switch ( hstream()->GetMode() ) {
	case ST_READ_UNICODE : {
		if ( counts > ( hstream()->GetSize() / sizeof( wchar_t ) ) ) {
			st_core_return( ST_ERR_OUTOFSIZE );
		} else if ( ! counts ) {
			ulTextNumbersResult = hstream()->GetSize() / sizeof( wchar_t );
		}
		for ( un32 un = 0; ( un < ulTextNumbersResult ); ++un ) {
			( *str ).Append( fgetwc( hfile() ) );
		}
		break;
	}
	case ST_READ_UTF8 : {
		if ( ! counts ) {
			ulTextNumbersResult = hstream()->GetSize();
		}
		for ( un32 un = 0; ( un < ulTextNumbersResult ) || ( ! hstream()->IsEOF() ); ++un ) {
			( *str ).Append( fgetwc( hfile() ) );
		}
		break;
	}
	default :
		st_core_return( ST_ERR_UNABLEREAD );
		break;
	}
	st_core_return( ST_NOERR );
}

/*
============
stStreamText::WriteText
============
*/
void stStreamText::WriteText( const un32 counts, const stStrW &str ) {
	if ( ! hstream() ) {
		st_core_return( ST_ERR_NULLSTREAMHANDLE );
	}
	if ( hstream()->GetMode() != ST_WRITE_UTF8 || hstream()->GetMode() != ST_WRITE_UNICODE ) {
		st_core_return( ST_ERR_UNABLEWRITE );
	}
	if ( counts > ( hstream()->GetSize() / sizeof( wchar_t ) ) ) {
		st_core_return( ST_ERR_OUTOFSIZE );
	}
	if ( ! fputws( str.Data(), hfile() ) ) {
		st_core_return( ST_ERR_WRITETEXT );
	}
	st_core_return( ST_NOERR );
}
