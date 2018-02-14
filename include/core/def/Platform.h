/**
 *  ƽ̨����
 */

#ifndef __STLIB_PLATFORM_H__
#define __STLIB_PLATFORM_H__

/** \defgroup ƽ̨��غ궨��
 *  ƽ̨��
 *  \{
 */

#ifdef         _WIN32
#	define                 WIN32_LEAN_AND_MEAN
#	include <Windows.h>
/** \brief Ŀ��32λWindows
 */
#	define                 _ST_PLATFORM_WIN32
#	pragma                 message( "Target Platform:[ WINDOWS ]" )

#	ifdef         _WIN64

/** \brief Ŀ��64λWindows
 */
#		define                 _ST_PLATFORM_WIN64
#		pragma                 message( "Target Platform:[ WINDOWSx64 ]" )
#	endif     /* !_WIN64 */

#elif defined( __linux__ )

/** \brief Ŀ��Linuxϵͳ
 */
#	define                 _ST_PLATFORM_LINUX
#	pragma                 message( "Target Platform:[ LINUX ]" )
           /* !__linux__ */


#   elif defined( __APPLE__ )
/**  \brief Ŀ��ƻ��OSX/macOSϵͳ
 */
#   define                 _ST_PLATFORM_APPLEOSX
#   pragma                 message( "Target Platform:[ APPLE OSX ]" )
           /* !__APPLE__ */

#else 
/**  \brief Ŀ��δ֪ϵͳ
 */
#   define                 _ST_PLATFORM_UNKNOWN
#   pragma                 message( "Target Compiler:[ UNKNOWN ]" )
#endif     /* !_WIN32 */
/** \} */ 

#endif /* !__STLIB_PLATFORM_H__ */