#include <malloc.h>
#include "..\include\core\Core.h"
#include "..\include\Enum.h"
#include "..\include\utils\Maths.h"
#include "..\include\base\Str.h"

using namespace stLibCore;
using namespace stLibUtils::Maths;

static stResult s_lastErr = 0;
/*
==============================================================

	stFunctionControl

==============================================================
*/
void			Discard( const stResult curStatus, const char *newFunctionName );
void *			Return( const stResult returnCode, stResult ncodeType, void **ppvarToReturn = NULL);

/*
============
Return
============
*/
void *Return( const stResult code, stResult ncodeType, void **ppvar ) {
	s_lastErr = code;
	if( code < 0 ) {
		throw s_curLocDesc;
	} else if ( ncodeType == stLibEnum::ST_CR_WARNNING ) {
		// warnning code can be ignored 
		return ( ppvar == NULL ) ? NULL : *ppvar;
	} else {
		// no error occurs.
		return ( ppvar == NULL ) ? NULL : *ppvar;
	}
}

/*
============
Discard
============
*/
void Discard( const stResult curStatus, const char *name ) {
	printf( "FUNCTION[ %s ] has been discarded in current version", name );
	throw s_curLocDesc;
}

/*
==============================================================

	Core operating adapters

==============================================================
*/

/*
============
HeapSize
============
*/
un32 stLibCore::HeapSize( void *memory ) {
	un32 memorySize = 0;

#ifdef _ST_DEBUG

	try {
		memorySize = _msize_dbg( memory, _NORMAL_BLOCK );
	} catch( ... ) {
		if ( NULL == memory ) {
			throw "Trying to get size of NULL pointer.";
		} else {
			throw "Failed to get size of memory which memory points to.";
		}
	}
#else /* !_ST_RELEASE */

	memorySize = _msize( memory );

#endif /* !_ST_DEBUG */

	return memorySize;
}

/*
============
CheckPtrNull
============
*/
void stLibCore::CheckPtrNull( void *memory ) {
	if ( NULL == memory ) {
		throw s_curLocDesc;
	}
}

/*
============
CoreReturn
============
*/
void stLibCore::CoreReturn( const stResult code, bool iswarnningCode ) {
	if ( iswarnningCode ) {
		Return( code, stLibEnum::ST_CR_WARNNING );
	} else {
		Return( code, stLibEnum::ST_CR_ERROR );
	}
}

/*
============
CoreDiscard
============
*/
void stLibCore::CoreDiscard( const stResult curStatus, const ch8 *name ) {
	Discard( curStatus, name );
}

/*
============
LastErrCode
============
*/
stResult stLibCore::LastErrCode() {
	return s_lastErr;
}

/*
============
SysLastErrDesc
============
*/
stStrW stLibCore::SysLastErrDesc() {
	stStrW	desc;

#ifdef _ST_PLATFORM_WIN32

	un32	dLastError = GetLastError();

	if ( dLastError != S_OK ) {
		void *lpMsgBuf = NULL;
		dLastError = dLastError;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			0,
			( LPTSTR )&lpMsgBuf,
			0,
			NULL );
		desc.SetStr( ( const wchar_t * )lpMsgBuf );
	}

#endif /* !_ST_PLATFORM_WIN32 */

	return desc;
}
