
/// \brief 核心组件
#ifndef __STLIB_CORE_H__
#define __STLIB_CORE_H__

class stStrW;

#include <stdio.h>
#include "Def.h"

#ifdef         ST_SWITCH_MEMORYPOOL_ON
#	include "MemPool.h"
#elif defined( ST_SWITCH_JEMALLOC_ON )
#	include "../$ref$/jemalloc.h"
			/* !ST_SWITCH_JEMALLOC_ON */
#elif defined( ST_SWITCH_MEMORYPOOL_OFF )
		   /* !ST_SWITCH_MEMORYPOOL_OFF */
#endif	   /* !ST_SWITCH_MEMORYPOOL_ON */

#ifdef		  ST_SWITCH_MT_SAFE_ON
#	include "..\base\Thread.h"

#elif defined( ST_SWITCH_MT_SAFE_OFF )
		   /* !ST_SWITCH_MT_SAFE_OFF */
#endif	   /* !ST_SWITCH_MT_SAFE_ON */

namespace stLibCore {

/// \see st_sys_heap_memory_size
un32 HeapSize( void *memory );

/// \see st_check_null_ptr
void CheckPtrNull( void *memory );

/// \see st_core_return \n
///		 st_core_return_with_var
///		 st_core_return_with_var_with_warnningcode
void CoreReturn( const stResult returnCode, bool iswarnningCode = false );

/// \see st_core_discard
void CoreDiscard( const stResult curStatus, const ch8 *newFunctionName );

/// \see st_last_err
stResult LastErrCode();

/// \see st_sys_last_err_desc
stStrW SysLastErrDesc();

static bool s_IsDebugMode = true; // 已弃用

static ch8	s_curLocDesc[ 2048 ];  // 当前运行位置的描述

} /* stLibCore */


/// \defgroup 核心操作宏定义
/// \brief 与底层操作相关的宏定义
/// \{

#ifdef         ST_SWITCH_ISDEBUGMODE_ON
/// \brief 记录当前程序错误的信息
/// \note  调试版本；s_IsDebugMode（已弃用），请使用ST_SWITCH_ISDEBUGMODE_ON来启用此功能
#	define st_sys_record_cur_loc_desc() \
	if ( stLibCore::s_IsDebugMode ) { \
		st_zero_memory( stLibCore::s_curLocDesc, 1 ); \
		sprintf( \
			stLibCore::s_curLocDesc, \
			"FILE: %s\nFUNCTION NAME: %s\nLINE: %d\nDATE: %s\nTIME: %s\n", \
			__FILE__, __FUNCTION__, __LINE__, __DATE__, __TIME__ ); \
	}
#elif defined( ST_SWITCH_ISDEBUGMODE_OFF )
/// \brief 记录当前程序错误的信息
/// \note  运行版本；s_IsDebugMode（已弃用），请使用ST_SWITCH_ISDEBUGMODE_ON来启用此功能
#	define st_sys_record_cur_loc_desc()
// to do nothing
#endif

/// \brief		检查一个指针是否为空
/// \param[in]	指针
#define st_check_null_ptr( memory ) \
	st_sys_record_cur_loc_desc() \
	stLibCore::CheckPtrNull( memory )

/// \brief		函数返回一个值
/// \note		用于非void函数
/// \param[in]	function_return_code 当前函数的最终错误代码
/// \param[in]	var_to_return		 当前函数的返回值
#define st_core_return_with_var( function_return_code, var_to_return ) \
	st_sys_record_cur_loc_desc() \
	stLibCore::CoreReturn( function_return_code ); \
	return var_to_return

/// \brief		函数返回一个值
/// \note		用于非void函数；最终错误代码应当非ST_NOERR且不会造成重大程序崩溃，仅作警告用的错误代码
/// \param[in]	function_return_code 当前函数的最终错误代码，且不能为ST_NOERR或造成重大程序崩溃
/// \param[in]	var_to_return		 当前函数的返回值
#define st_core_return_with_var_with_warnningcode( function_return_code, var_to_return ) \
	st_sys_record_cur_loc_desc() \
	stLibCore::CoreReturn( function_return_code, true ); \
	return var_to_return

/// \brief		函数不返回任何值
/// \note		用于void函数
/// \param[in]	function_return_code 当前函数的最终错误代码
#define st_core_return( function_return_code )  \
	st_sys_record_cur_loc_desc() \
	stLibCore::CoreReturn( function_return_code ); \
	return

/// \brief		函数已弃用
/// \note		提示函数已弃用
/// \param[in]	current_status 当前函数状态
/// \param[in]	new_function_name 提示新函数的函数签名
#define st_core_discard( current_status, new_function_name ) \
	st_sys_record_cur_loc_desc() \
	stLibCore::CoreDiscard( current_status, new_function_name )

#define st_core_return_success() \
	return ST_NOERR

/// \brief		返回记录的最后一个错误
#define st_last_err()  \
	stLibCore::LastErrCode()

/// \brief		获取系统API的错误信息
/// \note		（当前仅支持WIN32）
#define st_sys_last_err_desc() \
	stLibCore::SysLastErrDesc()

#ifdef         ST_SWITCH_MEMORYPOOL_ON

#	pragma message( "Target Switch:[ MEMORY POOL ] : ON" )
#	error "stLib memory pool has been discarded."
	/// \brief Gets a size of heap memory points to.  Others will cause a error.
	/// \param[in] memory Heap memory.
#	define st_sys_heap_memory_size( memory ) \
		stLibCore::stCore::HeapSize( memory )

	/// \brief  Get memory alloced by assigned method.
	/// \tparam new
	template<typename T>
	ST_INLINE static T *st_new( un64 objNum ) {
		return ( T* )( stMemPool::Instance().Alloc( objNum * sizeof( T ) ) );
	}

	template<typename T>
	ST_INLINE static T *st_new() {
		return ( T* )( stMemPool::Instance().Alloc( 1 * sizeof( T ) ) );
	}

	template<typename T>
	ST_INLINE static void st_delete( T **pt ) {
		stMemPool::Instance().Free( *pt );
	}

	template<typename T>
	ST_INLINE static void st_delete_arr( T **pt ) {
		stMemPool::Instance().Free( *pt );
	}

	template<typename T>
	ST_INLINE static T *st_new_class( const T& instance ) {
		T * const mem = ( T* )( stMemPool::Instance().Alloc( 1 * sizeof( T ) ) );
		memcpy( mem, &instance, sizeof( T ) );
		return mem;
	}

	template<typename T>
	ST_INLINE static void st_delete_class( T **pt ) {
		( *pt )->~T();
		stMemPool::Instance().Free( *pt );
	}


#elif defined( ST_SWITCH_JEMALLOC_ON )

#ifndef __STLIB_CORE_H_JEMALLOCINFOPRINTED //仅在控制台输出一次jemalloc版权信息
#define __STLIB_CORE_H_JEMALLOCINFOPRINTED
#	pragma message( "Target Switch:[ JEMALLOC ] : ON" )
#	pragma message( "\n----------------\njemalloc\n----------------\nhttps://github.com/jemalloc/jemalloc\n\nCopyright (C) 2002-2015 Jason Evans\n" )
#	pragma comment ( lib, "libjemalloc_x86_Release-Static.lib" )
#endif /* __STLIB_CORE_H_JEMALLOCINFOPRINTED */

#	ifdef	   _ST_DEBUG
#		pragma                 warning( disable : 4273 ) // jemalloc release lib.
#	endif  /* !_ST_DEBUG */
	extern "C" __declspec( dllexport ) void*	je_malloc( size_t size );
	extern "C" __declspec( dllexport ) void		je_free(void *ptr);
	extern "C" __declspec( dllexport ) size_t	je_malloc_usable_size( JEMALLOC_USABLE_SIZE_CONST void	*ptr);

	/// \brief		获取堆内存大小
	/// \note		（jemalloc版本）
	/// \param[in]	memory 堆内存指针
#	define st_sys_heap_memory_size( memory ) \
		je_malloc_usable_size( memory )

	/// \brief		分配连续的内存空间
	/// \note		不可用于类分配
	/// \param[in]  T 类型
	/// \param[in]	objNum 分配大小，以类型的个数为最小单位
	template<typename T>
	ST_INLINE static T *st_new( un64 objNum ) {
		return ( T * )je_malloc( objNum * sizeof( T ) );
	}

	/// \brief		分配单个类型大小的空间
	/// \note		不可用于类分配
	/// \param[in]  T 类型
	template<typename T>
	ST_INLINE static T *st_new() {
		return ( T * )je_malloc( 1 * sizeof( T ) );
	}

	/// \brief		释放分配的内存空间
	/// \note		不可用于类释放，不可释放连续堆内存空间
	/// \param[in]  T 类型
	/// \param[in]  pt 指针地址
	template<typename T>
	ST_INLINE static void st_delete( T **pt ) {
		je_free( *pt );
	}

	/// \brief		释放分配的内存空间
	/// \note		不可用于类释放，不可释放单个堆内存空间
	/// \param[in]  T 类型
	/// \param[in]  pt 指针地址
	template<typename T>
	ST_INLINE static void st_delete_arr( T **pt ) {
		je_free( *pt );
	}

	/// \brief		分配类堆内存空间
	/// \warning	不建议使用，COM组件与接口都存在野指针问题	
	/// \param[in]  T 类型
	/// \param[in]  instance T类型的实例，用帮助初始化；生命周期仅为本函数，请注意引用次数问题！
	template<typename T>
	ST_INLINE static T *st_new_class( const T& instance ) {
		T * const mem = ( T * )( je_malloc( 1 * sizeof( T ) ) );
		memcpy( mem, &instance, sizeof( T ) );
		return mem;
	}

	/// \brief		释放类对内存空间
	/// \warning	不建议使用
	/// \param[in]  T 类型
	/// \param[in]  pt 指针地址
	template<typename T>
	ST_INLINE static void st_delete_class( T **pt ) {
		( *pt )->~T();
		je_free( ( void * )( *pt ) );
	}

#elif defined( ST_SWITCH_MEMORYPOOL_OFF )
#	pragma message( "Target Switch:[ MEMORY POOL ] : OFF" )
	/// \brief 兼容编译

#	define st_sys_heap_memory_size( memory ) \
		stLibCore::HeapSize( memory )

	template<typename T>
	ST_INLINE static T *st_new( un64 objNum ) {
		return new T[ objNum ];
	}

	template<typename T>
	ST_INLINE static T *st_new() {
		return new T;
	}

	template<typename T>
	ST_INLINE static void st_delete( T **pt ) {
		st_safe_del( *pt );
	}

	template<typename T>
	ST_INLINE static void st_delete_arr( T **pt ) {
		st_safe_del_arr( *pt );
	}
	
	template<typename T>
	ST_INLINE static T *st_new_class( const T& instance ) {
		T * const mem = new T;
		memcpy( mem, &instance, sizeof( T ) );
		return mem;
	}

	template<typename T>
	ST_INLINE static void st_delete_class( T **pt ) {
		st_safe_del( *pt );
	}

           /* !ST_SWITCH_MEMORYPOOL_OFF */

#endif     /* !ST_SWITCH_MEMORYPOOL_ON */


#ifdef		  ST_SWITCH_MT_SAFE_ON

	/// \brief 快速锁定代码段
	/// \param[in] code 需要锁定的代码段
	/// \param[in] cs   临界区域
	/// \see stCriticalSection
#	define st_atomic( code, cs ) \
	cs.Lock(); \
	code; \
	cs.Unlock()

#elif defined( ST_SWITCH_MT_SAFE_OFF )
	/// \brief 兼容编译
#	define st_atomic( code,cs ) \
	code

		   /* !ST_SWITCH_MT_SAFE_OFF */
#endif     /* !ST_SWITCH_MT_SAFE_ON */

#define ST_CORE_FORECE_SINGLE_INSTANCE_WIN32__BEGIN( uniID ) \
	HANDLE __h_st_single_instance_mutex__ = CreateMutex( NULL, false, uniID );\
	if ( GetLastError() == ERROR_ALREADY_EXISTS ) { \
		CloseHandle( __h_st_single_instance_mutex__ );

#define ST_CORE_FORECE_SINGLE_INSTANCE_WIN32__END() }

/** 一个最简单的例子
	ST_CORE_FORECE_SINGLE_INSTANCE_WIN32__BEGIN( "uniID" ) {
		return 0;
	}
	ST_CORE_FORECE_SINGLE_INSTANCE_WIN32__END();
*/

/// \}


#endif /* !__STLIB_CORE_H__ */
