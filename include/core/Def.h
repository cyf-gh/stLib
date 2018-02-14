/**
 *	\breif 定义了基本的stLib事项；该文件必须引用在所有的stLib文件之前
 */

#ifndef __STLIB_DEF_H__
#define __STLIB_DEF_H__

#include <cstdint>

/** \defgroup 基本类型
 *  stLib所定义的基本类型
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

/** \ingroup 宏定义
 *  \{
 */

/** \brief		   将每个内存空间置空
 *	\param[in] p   内存指针
 *	\param[in] len 内存大小
 */
#define st_zero_memory( p, len ) \
	memset( p, 0, len )	

/** \brief		      是否为错误的返回值
 *	\param[in] result 错误代码
 */
#define st_do_err( result )	\
	( ( ( stResult ) ( result ) ) < 0 )

/** \brief		   安全释放COM对象
 *	\param[in out] COM指针
 */
#define st_safe_rel( p ) \
if( p != NULL ) { \
	p->Release(); \
	p = NULL; \
}

/** \brief 强制类使其无法进行二进制拷贝
 *  \param class_name 类名
 */
#define st_class_no_bin_cpy( class_name ) \
public: \
    class_name &operator=( const class_name& rhs ) = delete;

/** \} */ 

#define ST_NOERR				( ( stResult ) 0  )
#define ST_NOERR_INTERNAL		( ( stResult ) 10 )

/** \brief 不使用stLib自带宏开关定义 */
#ifndef ST_DEF_DONOTUSESTLIBSWITCH
#include "..\Switch.h"
#endif /* !ST_DEF_DONOTUSESTLIBSWITCH */

#include "def\Platform.h"
#include "def\Build.h"

#ifdef __cplusplus

/** \brief 释放单个堆内存
 *  \see   st_new
 *		   st_new_class
 */
#	define st_safe_del( p ) \
if ( p != NULL ) { \
	delete p; \
	p = NULL; \
}

/** \brief 释放连续堆内存
 *  \see   st_delete_class
 *		   st_delete
 */
#	define st_safe_del_arr( p ) \
if ( p != NULL ) { \
	delete [] p; \
	p = NULL; \
}

#	include "def\COMstd.h"

#endif /* !__cplusplus */

/** \} */ 

#endif /* !__STLIB_DEF_H__ */
