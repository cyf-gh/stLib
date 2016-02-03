/*

Provides core error record of stLib.

*/

#ifndef __STLIB_CORE_H__
#define __STLIB_CORE_H__

class stStrW;

#include <stdio.h>
#include "Def.h"

#ifdef         ST_SWITCH_MEMORYPOOL_ON
#	include "MemPool.h"
#elif defined( ST_SWITCH_JEMALLOC_ON )
#	include "jemalloc.h"
			/* !ST_SWITCH_JEMALLOC_ON */
#elif defined( ST_SWITCH_MEMORYPOOL_OFF )
		   /* !ST_SWITCH_MEMORYPOOL_OFF */
#endif	   /* !ST_SWITCH_MEMORYPOOL_ON */

#ifdef		  ST_SWITCH_MT_SAFE_ON
#	include "Thread.h"

#elif defined( ST_SWITCH_MT_SAFE_OFF )
		   /* !ST_SWITCH_MT_SAFE_OFF */
#endif	   /* !ST_SWITCH_MT_SAFE_ON */

namespace stLibCore {

/***********************************************************************

  stCore

***********************************************************************/

class stCore {

	class stFunctionControl;
	class stCurLocDesc;

private:
								stCore();
								stCore( const stCore & );
								~stCore() { }

public:
	static stFunctionControl *	m_controller;
	static stCurLocDesc	*		m_desc;

	static un32					HeapSize( void *memory );
	static void					CheckPtrNull( void *memory );

	static void					CoreReturn( const stResult returnCode );
	static void					CoreDiscard( const stResult curStatus, const char *newFunctionName );

	static stResult				LastErrCode();

	static stStrW				SysLastErrDesc();
};

/***********************************************************************

  Common

***********************************************************************/

#ifdef		_ST_DEBUG
#	pragma message( "Target Switch:[ stLib DETAILED INFO ] : ON" )
	static char					s_curLocDesc[ 2048 ];  // info description string.

	/*
	============
	st_sys_record_cur_loc_desc

	Records the current code location detail.
	============
	*/
	#define st_sys_record_cur_loc_desc() \
		st_zero_memory( stLibCore::s_curLocDesc, 1 ); \
		sprintf( \
			stLibCore::s_curLocDesc, \
			"FILE: %s\nFUNCTION NAME: %s\nLINE: %d\nDATE: %s\nTIME: %s\n", \
			__FILE__, __FUNCTION__, __LINE__, __DATE__, __TIME__ )

#else	/* !_ST_DEBUG */
#	pragma message( "Target Switch:[ ERROR INFO ] : OFF" )
	static char					s_curLocDesc[ 1 ];  // info description string.

#	define st_sys_record_cur_loc_desc();

#endif  /* !_ST_RELEASE */

/*
============
st_check_null_ptr
============
*/
#define st_check_null_ptr( memory ) \
	st_sys_record_cur_loc_desc(); \
	stLibCore::stCore::CheckPtrNull( memory )
/*
============
st_core_return
============
*/
#define st_core_return_with_var( function_return_code, var_to_return ) \
	st_sys_record_cur_loc_desc(); \
	stLibCore::stCore::CoreReturn( function_return_code ); \
	return var_to_return

#define st_core_return( function_return_code )  \
	st_sys_record_cur_loc_desc(); \
	stLibCore::stCore::CoreReturn( function_return_code ); \
	return
/*
============
st_core_discard
============
*/
#define st_core_discard( current_status, new_function_name ) \
	st_sys_record_cur_loc_desc(); \
	return stLibCore::stCore::CoreDiscard( current_status, new_function_name )
/*
============
st_last_err
============
*/
#define st_last_err()  \
	stLibCore::stCore::LastErrCode()
/*
============
st_sys_last_err_desc

Returns current system API last error.
============
*/
#define st_sys_last_err_desc() \
	stLibCore::stCore::SysLastErrDesc()

/***********************************************************************

  Memory pool

***********************************************************************/

#ifdef         ST_SWITCH_MEMORYPOOL_ON

#	pragma message( "Target Switch:[ MEMORY POOL ] : ON" )
#	error "stLib memory pool has been discarded."
	/*
	============
	st_sys_heap_memory_size

	Returns a size of heap memory points to.  Others will cause a error.
	============
	*/
#	define st_sys_heap_memory_size( memory ) \
		stLibCore::stCore::HeapSize( memory )

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
#	pragma message( "Target Switch:[ JEMALLOC ] : ON" )
#	pragma message( "\n----------------\njemalloc\n----------------\nhttps://github.com/jemalloc/jemalloc\n\nCopyright (C) 2002-2015 Jason Evans\n" )
#	pragma comment ( lib, "libjemalloc_x86_Release-Static.lib" )

#	ifdef	   _ST_DEBUG
#		pragma                 warning( disable : 4273 ) // jemalloc release lib.
#	endif  /* !_ST_DEBUG */
	extern "C" __declspec( dllexport ) void*	je_malloc( size_t size );
	extern "C" __declspec( dllexport ) void		je_free(void *ptr);
	extern "C" __declspec( dllexport ) size_t	je_malloc_usable_size(
	JEMALLOC_USABLE_SIZE_CONST void	*ptr);

	/*
	============
	st_sys_heap_memory_size

	Returns a size of jemalloced heap memory points to.
	============
	*/
#	define st_sys_heap_memory_size( memory ) \
		stLibCore::je_malloc_usable_size( memory )

	template<typename T>
	ST_INLINE static T *st_new( un64 objNum ) {
		return ( T * )je_malloc( objNum * sizeof( T ) );
	}

	template<typename T>
	ST_INLINE static T *st_new() {
		return ( T * )je_malloc( 1 * sizeof( T ) );
	}

	template<typename T>
	ST_INLINE static void st_delete( T **pt ) {
		je_free( *pt );
	}

	template<typename T>
	ST_INLINE static void st_delete_arr( T **pt ) {
		je_free( *pt );
	}

	template<typename T>
	ST_INLINE static T *st_new_class( const T& instance ) {
		T * const mem = ( T * )( je_malloc( 1 * sizeof( T ) ) );
		memcpy( mem, &instance, sizeof( T ) );
		return mem;
	}

	template<typename T>
	ST_INLINE static void st_delete_class( T **pt ) {
		( *pt )->~T();
		je_free( ( void * )( *pt ) );
	}

#elif defined( ST_SWITCH_MEMORYPOOL_OFF )
#	pragma message( "Target Switch:[ MEMORY POOL ] : OFF" )

	/*
	============
	st_sys_heap_memory_size

	Returns a size of heap memory points to.  Others will cause a error.
	============
	*/
#	define st_sys_heap_memory_size( memory ) \
		stLibCore::stCore::HeapSize( memory )

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

/***********************************************************************

  MT Safe

***********************************************************************/
#ifdef		  ST_SWITCH_MT_SAFE_ON
	stCriticalSection s_globalCS;

	/*
	============
	st_atomic
	============
	*/
#	define st_atomic( code ) \
	s_globalCS.Lock(); \
	code; \
	s_globalCS.Unlock()

#elif defined( ST_SWITCH_MT_SAFE_OFF )
#	define st_atomic( code ) \
	code

		   /* !ST_SWITCH_MT_SAFE_OFF */
#endif     /* !ST_SWITCH_MT_SAFE_ON */

} /* stLibCore */

#endif /* !__STLIB_CORE_H__ */
