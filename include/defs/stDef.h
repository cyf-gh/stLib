/**
 *	Defines bases of stLib.  This file should be included at the beginning of the program.
 */

#ifndef __STLIB_DEF_H__
#define __STLIB_DEF_H__

#include <cstdint>

#include "stForwardDecls.h"

/** \defgroup basetype Types Base
 *  Basic types defined by stLib.
 *  \{
 */
typedef char			ch8;
typedef int8_t			n8;
typedef int16_t		    n16;
typedef int32_t		    n32, stResult;
typedef int64_t		    n64;
typedef uint8_t		    un8, byte8;
typedef uint16_t		un16;
typedef uint32_t		un32;
typedef uint64_t		un64;
typedef float			f32;
typedef double			f64;
/** \} */

namespace_stLib {

template<typename type_of_char>
struct st_result_detail {
	stResult errCode;
	const type_of_char *description;
};

typedef st_result_detail<wchar_t> ST_RESULTW;
typedef st_result_detail<char> ST_RESULTA;

static const ST_RESULTW g_result_null_w = { -9999, L"" };
static const ST_RESULTA g_result_null_A = { -9999, "" };

}
/** \ingroup Basic Macro Functions
 *  \{
 */

/** \brief		   Set each block to NULL.
 *	\param[in] p   Pointer.
 *	\param[in] len Length of memory.
 */
#define st_zero_memory( p, len ) \
	memset( p, 0, len )

/** \brief		   Safely release a COM object.
 *	\param[in out] p Pointer points to a COM object.
 */
#define st_safe_rel( p ) \
if( p != nullptr ) { \
	p->Release(); \
	p = nullptr; \
}

/** \brief 				Safely delete a single object.
 *  \param[in out]	p 	Pointer points to a single object in heap.
 */
#	define st_safe_del( p ) \
if ( p != nullptr ) { \
	delete p; \
	p = nullptr; \
}

/** \brief 				Safely delete an array.
 *  \param[in out]	p 	Pointer points to an array in heap.
 */
#	define st_safe_del_arr( p ) \
if ( p != nullptr ) { \
	delete [] p; \
	p = nullptr; \
}

#	define st_instance_template_class_in_cpp( class_name, instance_type ) \
template class class_name<instance_type>;

/** \} */

/*
 * Compilers
 */
#ifdef        _MSC_VER

#	pragma					warning( disable : 4996 )
#	define					ST_INLINE  __forceinline
#	pragma					message( "Target Compiler:[ MSVC ]" )

           /* !_MSC_VER */

#	elif defined( __GNUC__ )

#	define					ST_INLINE inline
#	pragma					message( "Target Compiler:[ GCC ]" )

#	else

#	define					ST_INLINE inline
#	pragma					message( "Target Compiler:[ UNKNOWN ]" )

#endif     /* !__GNUC__ */

/** \defgroup 平台相关宏定义
 *  平台宏
 *  \{
 */

#ifdef						_WIN32
#	define                 WIN32_LEAN_AND_MEAN
#	include <Windows.h>
/** \brief 目标32位Windows
 */
#	define					un un32
#	define					nbus  n32
#	define                 _ST_PLATFORM_WIN32
#	pragma                 message( "Target Platform:[ WIN32 ]" )

#	ifdef					_WIN64
#	define					un un64
#	define					nbus  n64
/** \brief 目标64位Windows
 */
#	define                 _ST_PLATFORM_WIN64
#	pragma                 message( "Target Platform:[ WIN64 ]" )
#	endif /* !_WIN64 */

#	elif defined( __linux__ )

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

#	else 
/**  \brief 目标未知系统
 */
#   define                 _ST_PLATFORM_UNKNOWN
#   pragma                 message( "Target Platform:[ UNKNOWN ]" )
/** \} */ 
#endif /* !_WIN32 */

#endif /* !__STLIB_DEF_H__ */
