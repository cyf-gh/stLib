#include "..\include\core\Core.h"
#include "..\include\core\ErrCode.h"
#include "..\include\base\Stream.h"
#include "..\include\base\Str.h"

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
	if ( m_pfile != NULL ) {
		Close();
	}
}

/*
============
stStream::Open
============
*/
void stStream::Open( const stStrW &path, FILEOPENMODE mode ) {
	if ( m_pfile ) {
		st_core_return( ST_ERR_OPENEDFILEHANDLE );
	}
	switch ( mode ) {
		// Unicode mode
		case ST_WRITE_UNICODE :
			m_pfile = _wfopen( path.Data(), L"rt+,ccs=UNICODE" );
			break;
		case ST_READ_UNICODE :
			m_pfile = _wfopen( path.Data(), L"rt,ccs=UNICODE" );
			break;
		case ST_CREATE_UNICODE :
			m_pfile = _wfopen( path.Data(), L"wt+,ccs=UNICODE" );
			break;
		// UTF-8
		case ST_WRITE_UTF8 :
			m_pfile = _wfopen( path.Data(), L"rt+,ccs=UTF-8" );
			break;
		case ST_READ_UTF8 :
			m_pfile = _wfopen( path.Data(), L"rt,ccs=UTF-8" );
			break;
		case ST_CREATE_UTF8 :
			m_pfile = _wfopen( path.Data(), L"wt+,ccs=UTF-8" );
		// ASCI
		case ST_WRITE_ASCI :
			m_pfile = _wfopen( path.Data(), L"rt+" );
			break;
		case ST_READ_ASCI :
			m_pfile = _wfopen( path.Data(), L"rt" );
			break;
		case ST_CREATE_ASCI :
			m_pfile = _wfopen( path.Data(), L"wt" );
			break;
		// Binary
		case ST_WRITE_BINARY :
			m_pfile = _wfopen( path.Data(), L"rb+" );
			break;
		case ST_READ_BINARY :
			m_pfile = _wfopen( path.Data(), L"rb" );
			break;
		case ST_CREATE_BINARY :
			m_pfile = _wfopen( path.Data(), L"wb" );
			break;
		default:
			st_core_return( ST_ERR_UNKNOWNOPENMODE );
	}
	if ( !m_pfile ) {
		st_core_return( ST_ERR_OPENFILEHANDLE );
	}
	// get size of file
	Move( 0L, ST_END );
	m_size = Pos();
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
	if ( EOF == fclose( m_pfile ) ) {
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
	if ( 0 != fseek( m_pfile, pos, org ) ) {
		st_core_return( org );
	}
	st_core_return( ST_NOERR );
}

/*
============
stStream::Save
============
*/
void stStream::Save() {
	if ( ! m_pfile ) {
		st_core_return( ST_ERR_NULLFILEHANDLE );
	}
	if ( fflush( m_pfile ) != 0 ) {
		st_core_return( ST_ERR_FLUSHFILE );
	}
	st_core_return( ST_NOERR );
}

/*
============
stStream::SaveAs
============
*/
void stStream::SaveAs( const stStrW &newPath ) {
	FILE   *pnew	  = _wfopen( newPath.Data(), L"wb" );
	byte8  c		  = 0;
	const un32 orgPos = Pos();

	if ( !pnew ) {
		st_core_return( ST_ERR_CREATECLONEFILE );
	}
	MoveHead();
	for( un32 i = 0; i < Size(); ++i ) { 
		c = fgetc( m_pfile );
        fputc( c, pnew );
    }
	Save();
	if ( EOF == fclose( pnew ) ) {
		st_core_return( ST_ERR_CLOSECLONEFILE );
	}
	Move( orgPos, ST_HEAD );
	st_core_return( ST_NOERR );
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
	: m_pparent( pParent ) { }

stStreamHelper::stStreamHelper()
	: m_pparent( NULL ) { }

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
stStreamBinary::~stStreamBinary() { }

/*
============
stStreamBinary::ReadBytes
============
*/
void stStreamBinary::ReadBytes( const un32 counts, byte8 **ppdata ) {
	un32 size = counts;

	if ( ! hstream() ) {
		st_core_return( ST_ERR_NULLSTREAMHANDLE );
	}
	if ( ST_READ_BINARY != hstream()->Mode() ) {
		st_core_return( ST_ERR_UNABLEREAD );
	}
	if ( counts > hstream()->Size() ) {
		st_core_return( ST_ERR_OUTOFSIZE );
	} else if ( ! counts ) {
		size = hstream()->Size();
	}

	if( ! fread( * ppdata, sizeof( byte8 ), size, hfile() ) ) {
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
	if ( ST_WRITE_BINARY != hstream()->Mode() ) {
		st_core_return( ST_ERR_UNABLEWRITE );
	}
	//if ( counts > hstream()->Size() ) {
	//	st_core_return( ST_ERR_OUTOFSIZE );
	//}
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
stStreamText::stStreamText( stStream *pparent  )
	: stStreamHelper( pparent ) { }

stStreamText::stStreamText()
	: stStreamHelper( NULL ) { }

/*
============
stStreamText::~stStreamText
============
*/
stStreamText::~stStreamText() { }

/*
============
stStreamText::ReadText
============
*/
void stStreamText::ReadText( const un32 counts, stStrW *str ) {
	un32 totalTextsCount = counts;

	if ( ! hstream() ) {
		st_core_return( ST_ERR_NULLSTREAMHANDLE );
	}
	switch ( hstream()->Mode() ) {
	case ST_READ_UNICODE : {
		if ( counts > ( hstream()->Size() ) ) {
			st_core_return( ST_ERR_OUTOFSIZE );
		} else if ( ! counts ) {
			totalTextsCount = hstream()->Size();
		}
		for ( un32 un = 0; ( un < totalTextsCount ); ++un ) {
			str->Append( fgetwc( hfile() ) );
		}
		str->Data()[totalTextsCount] = L'\0';
		break;
	}
	case ST_READ_UTF8 : {
		if ( ! counts ) {
			totalTextsCount = hstream()->Size();
		}
		for ( un32 un = 0; ( un < totalTextsCount ) || ( ! hstream()->IsEOF() ); ++un ) {
			str->Append( fgetwc( hfile() ) );
		}
		str->Data()[totalTextsCount] = L'\0';
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
	if ( ! ( ( hstream()->Mode() == ST_WRITE_UTF8 ) || ( hstream()->Mode() == ST_WRITE_UNICODE ) ) ) {
		st_core_return( ST_ERR_UNABLEWRITE );
	}
	if ( counts > hstream()->Size() ) {
		st_core_return( ST_ERR_OUTOFSIZE );
	}
	if ( fputws( str.Data(), hfile() ) < 0 ) {
		st_core_return( ST_ERR_WRITETEXT );
	}
	st_core_return( ST_NOERR );
}

stStrW *stStreamText::AddUnicodeBoom( stStrW * pstr ) {
	return &pstr->Insert( 0, L"\uFEFF" );
}
