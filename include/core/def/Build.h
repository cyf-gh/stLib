/**
 *  项目生成有关的宏定义
 */

#ifndef __STLIB_BUILD_H__
#define __STLIB_BUILD_H__

/** \defgroup 生成宏定义
 *  生成与编译器相关的宏定义
 *  \{
 */
#ifdef         _DEBUG
#	define                 _ST_DEBUG
#	pragma                 message( "Target Build Mode:[ DEBUG ]" )

#elif defined( _ST_DB_ENABLE )
#	define                 _ST_DEBUG
#	pragma                 message( "Target Build Mode:[ DEBUG ]" )
           /* !_ST_DB_ENABLE */

#else
#	define                 _ST_RELEASE
#	pragma                 message( "Target Build Mode:[ RELEASE ]" )
           /* !_ST_RELEASE */

#endif     /* !_DEBUG */


#ifdef        _MSC_VER

#	pragma                 warning( disable : 4996 ) // 使用非安全标准库函数
#	define                 ST_INLINE  __forceinline
#	pragma                 message( "Target Compiler:[ MSVC ]" )

           /* !_MSC_VER */

#elif defined( __GNUC__ )

#	define                 ST_INLINE inline
#	pragma                 message( "Target Compiler:[ GCC ]" )

#endif     /* !__GNUC__ */
/** \} */ 

#endif /* !__STLIB_BUILD_H__ */