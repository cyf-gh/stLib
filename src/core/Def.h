/*

Base stLib type and macro defines.

*/

#ifndef __STLIB_DEF_H__
#define __STLIB_DEF_H__

#include <cstdint>

/***********************************************************************

    Platform

***********************************************************************/
#ifdef         _WIN32
#define                 WIN32_LEAN_AND_MEAN
#include <Windows.h>
#define                 _ST_PLATFORM_WIN32

#ifdef         _WIN64
#define                 _ST_PLATFORM_WIN64

#endif     /* !_WIN64 */

#elif defined( __linux__ )
#define                 _ST_PLATFORM_LINUX
           /* !__linux__ */

#elif defined( __APPLE__ )
#define                 _ST_PLATFORM_APPLEOSX
           /* !__APPLE__ */
#else
#define                 _ST_PLATFORM_UNKNOWN
#endif     /* !_WIN32 */

/***********************************************************************

    Build Mode

***********************************************************************/
#ifdef         _DEBUG
#define                 _ST_DEBUG

#elif defined( _ST_DB_ENABLE )
#define                 _ST_DEBUG
           /* !_ST_DB_ENABLE */
#else
#define                 _ST_RELEASE
#endif     /* !_DEBUG */

/***********************************************************************

    Compiler

***********************************************************************/
#ifdef        _MSC_VER

#pragma                 warning( disable : 4996) // Using unsafe functions.
#define                 ST_INLINE  __forceinline

           /* !_MSC_VER */

#elif defined( __GNUC__ )

#define                 ST_INLINE inline

#endif     /* !__GNUC__ */

/***********************************************************************

    Base type

***********************************************************************/
typedef char			ch8;
typedef int8_t			n8;
typedef int16_t			n16;
typedef int32_t			n32, stResult;
typedef int64_t			n64;
typedef uint8_t			un8, byte8;
typedef uint16_t		un16;
typedef uint32_t		un32;
typedef uint64_t		un64;
typedef float			f32;
typedef double			f64;

#define st_safe_del( p )		{ if ( p != NULL ) { delete p;	p = NULL; } }
#define st_safe_del_arr( p )	{ if ( p != NULL ) { delete [] p; p = NULL; } }
#define st_safe_rel( p )		{ if( p != NULL ) { p->Release(); p = NULL; } }
#define st_zero_memory( p, len )memset( p, 0, len )
#define st_do_err( result )		( ( ( stResult ) ( result ) ) < 0 )

// Takes small error, making application still run.  Puts logs on console.
#define ST_ERR_LEVEL1_UPPER_BOUND	( ( stResult ) -1	  )
// Takes serious error, and application have to abort.  Gives a throw.
#define ST_ERR_LEVEL2_UPPER_BOUND	( ( stResult ) -5001  )
// BOOM
#define ST_ERR_LEVEL3_UPPER_BOUND	( ( stResult ) -10001 )
#define ST_NOERR					( ( stResult ) 0	  )

#endif /* !__STLIB_DEF_H__ */
