/**
 *  平台定义
 */

#ifndef __STLIB_PLATFORM_H__
#define __STLIB_PLATFORM_H__

/** \defgroup 平台相关宏定义
 *  平台宏
 *  \{
 */

#ifdef         _WIN32
#	define                 WIN32_LEAN_AND_MEAN
#	include <Windows.h>
/** \brief 目标32位Windows
 */
#	define                 _ST_PLATFORM_WIN32
#	pragma                 message( "Target Platform:[ WINDOWS ]" )

#	ifdef         _WIN64

/** \brief 目标64位Windows
 */
#		define                 _ST_PLATFORM_WIN64
#		pragma                 message( "Target Platform:[ WINDOWSx64 ]" )
#	endif     /* !_WIN64 */

#elif defined( __linux__ )

/** \brief 目标Linux系统
 */
#	define                 _ST_PLATFORM_LINUX
#	pragma                 message( "Target Platform:[ LINUX ]" )
           /* !__linux__ */


#   elif defined( __APPLE__ )
/**  \brief 目标苹果OSX/macOS系统
 */
#   define                 _ST_PLATFORM_APPLEOSX
#   pragma                 message( "Target Platform:[ APPLE OSX ]" )
           /* !__APPLE__ */

#else 
/**  \brief 目标未知系统
 */
#   define                 _ST_PLATFORM_UNKNOWN
#   pragma                 message( "Target Compiler:[ UNKNOWN ]" )
#endif     /* !_WIN32 */
/** \} */ 

#endif /* !__STLIB_PLATFORM_H__ */