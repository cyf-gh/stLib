/**
 *  Platform macros define.
 */

#ifndef __STLIB_PLATFORM_H__
#define __STLIB_PLATFORM_H__

/** \defgroup platform Macros Platform 
 *  Platform macros.
 *  \{
 */

#ifdef         _WIN32
#	define                 WIN32_LEAN_AND_MEAN
#	include <Windows.h>
/** \brief Target OS Windows 32bit.
 */
#	define                 _ST_PLATFORM_WIN32
#	pragma                 message( "Target Platform:[ WINDOWS ]" )

#	ifdef         _WIN64

/** \brief Target OS Windows 64bit.
 */
#		define                 _ST_PLATFORM_WIN64
#		pragma                 message( "Target Platform:[ WINDOWSx64 ]" )
#	endif     /* !_WIN64 */

#elif defined( __linux__ )

/** \brief Target OS LINUX.
 */
#	define                 _ST_PLATFORM_LINUX
#	pragma                 message( "Target Platform:[ LINUX ]" )
           /* !__linux__ */


#   elif defined( __APPLE__ )
/**  \brief Target OS APPLE OSX.
 */
#   define                 _ST_PLATFORM_APPLEOSX
#   pragma                 message( "Target Platform:[ APPLE OSX ]" )
           /* !__APPLE__ */

#else 
/**  \brief Target OS UNKNOWN.
 */
#   define                 _ST_PLATFORM_UNKNOWN
#   pragma                 message( "Target Compiler:[ UNKNOWN ]" )
#endif     /* !_WIN32 */
/** \} */ 

#endif /* !__STLIB_PLATFORM_H__ */