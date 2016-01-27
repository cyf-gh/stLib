#include <malloc.h>
#include "..\include\core\Core.h"
#include "..\include\utils\Maths.h"
#include "..\include\base\Str.h"

using namespace stLibCore;
using namespace stLibUtils::Maths;

/*
==============================================================

	stCore

==============================================================
*/


/*
==============================================================

	stFunctionControl

==============================================================
*/

class stCore::stFunctionControl {

	friend class stCore;

private:
	stResult		m_lastErr;

public:
	void			Discard( const stResult curStatus, const char *newFunctionName );
	void *			Return( const stResult returnCode, void **ppvarToReturn = NULL );

					stFunctionControl() : m_lastErr( ST_NOERR ) { }
					~stFunctionControl() { };
};

/*
============
stCore::m_controller
============
*/
stCore::stFunctionControl *stCore::m_controller = new stCore::stFunctionControl();

/*
============
stCore::stFunctionControl::Return
============
*/
void *stCore::stFunctionControl::Return( const stResult code, void **ppvar ) {
	m_lastErr = code;
	if( IsIn( ST_ERR_LEVEL1_UPPER_BOUND, ST_ERR_LEVEL2_UPPER_BOUND, code ) ) {
		printf( "%s", s_curLocDesc );
		return NULL;
	} else if( IsIn( ST_ERR_LEVEL3_UPPER_BOUND, ST_ERR_LEVEL2_UPPER_BOUND, code ) ) {
		throw s_curLocDesc;
		return NULL;
	} else {
		// no error occurs.
		return NULL;
	}
	return ( ppvar == NULL ) ? NULL : *ppvar;
}

/*
============
stCore::stFunctionControl::Discard
============
*/
void stCore::stFunctionControl::Discard( const stResult curStatus, const char *name ) {
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
stCore::HeapSize
============
*/
un32 stCore::HeapSize( void *memory ) {
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
stCore::CheckPtrNull
============
*/
void stCore::CheckPtrNull( void *memory ) {
	if ( NULL == memory ) {
		throw s_curLocDesc;
	}
}

/*
============
stCore::CoreReturn
============
*/
void stCore::CoreReturn( const stResult code ) {
	m_controller->Return( code, NULL );
}

/*
============
stCore::CoreDiscard
============
*/
void stCore::CoreDiscard( const stResult curStatus, const char *name ) {
	m_controller->Discard( curStatus, name );
}

/*
============
stCore::LastErrCode
============
*/
stResult stCore::LastErrCode() {
	return m_controller->m_lastErr;
}

/*
============
stCore::SysLastErrDesc
============
*/
stStrW stCore::SysLastErrDesc() {
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
