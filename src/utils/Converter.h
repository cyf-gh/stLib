/*

Base class for base type converts.

*/
#ifndef __STLIB_CONVERTER_H__
#define __STLIB_CONVERTER_H__

#include <stdlib.h>
#include <stdio.h>
#include "..\core\Def.h"

namespace stLibUtils {

/***********************************************************************

  stConverter

***********************************************************************/

class stConverter {	
public:
	static n32			aTon32( const char *str );
	static n64			aTon64( const char *str );
	static f64			aTof64( const char *str );
	static n32			wTon32( const wchar_t *str );
	static n64			wTon64( const wchar_t *str );
	static f64			wTof64( const wchar_t *str  );
	static wchar_t *	ToStringW( wchar_t *str, const f64 digit );
	static char *		ToString( char *str, const f64 digit );
};

ST_INLINE n32 stConverter::aTon32( const char *str ) {
	return atoi( str );
}

ST_INLINE n64 stConverter::aTon64( const char *str ) {
	return atol( str );
}

ST_INLINE f64 stConverter::aTof64( const char *str ) {
	return atof( str );
}

ST_INLINE n32 stConverter::wTon32( const wchar_t *str ) {  
	return _wtoi( str );
}

ST_INLINE n64 stConverter::wTon64( const wchar_t *str ) {
	return _wtoi64( str );
}

ST_INLINE f64 stConverter::wTof64( const wchar_t *str  ) {
	return _wtof( str );
}

ST_INLINE wchar_t *stConverter::ToStringW( wchar_t *str, const f64 digit ) {
	swprintf( str, L"%lf", digit );
	return str;
}

ST_INLINE char *stConverter::ToString( char *str, const f64 digit ) {
	sprintf( str, "%lf", digit );
	return str;
}

} /* stLibUtils */

#endif /* !__STLIB_CONVERTER_H__ */
