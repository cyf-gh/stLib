
/// \brief The core components.
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
#	include "Thread.h"

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
void CoreReturn( const stResult returnCode );

/// \see st_core_discard
void CoreDiscard( const stResult curStatus, const char *newFunctionName );

/// \see st_last_err
stResult LastErrCode();

/// \see st_sys_last_err_desc
stStrW SysLastErrDesc();

static bool s_IsDebugMode = true; // discarded

static char	s_curLocDesc[ 2048 ];  // info description string.

} /* stLibCore */


/// \defgroup coremacros Macros Core Operation 
/// \brief Macros related to base code. 
/// \{

#ifdef         ST_SWITCH_ISDEBUGMODE_ON
/// \brief Records current error descriptions.
/// \note  Switches by s_IsDebugMode.
#	define st_sys_record_cur_loc_desc() \
	if ( stLibCore::s_IsDebugMode ) { \
		st_zero_memory( stLibCore::s_curLocDesc, 1 ); \
		sprintf( \
			stLibCore::s_curLocDesc, \
			"FILE: %s\nFUNCTION NAME: %s\nLINE: %d\nDATE: %s\nTIME: %s\n", \
			__FILE__, __FUNCTION__, __LINE__, __DATE__, __TIME__ ); \
	}
#elif defined( ST_SWITCH_ISDEBUGMODE_OFF )
/// \brief Records current error descriptions.
/// \note  Switches by s_IsDebugMode.
#	define st_sys_record_cur_loc_desc()
// to do nothing
#endif

/// \brief		Check if the pointer points to NULL.
/// \param[in]	memory Memory pointer.
#define st_check_null_ptr( memory ) \
	st_sys_record_cur_loc_desc() \
	stLibCore::CheckPtrNull( memory )

/// \brief		Function returns with a var.
/// \note		Used by non void functions.
/// \param[in]	function_return_code Error code of function.
/// \param[in]	var_to_return		 Returned var of function.
#define st_core_return_with_var( function_return_code, var_to_return ) \
	st_sys_record_cur_loc_desc() \
	stLibCore::CoreReturn( function_return_code ); \
	return var_to_return

/// \brief		Function returns with nothing.
/// \note		Used by void functions.
/// \param[in]	function_return_code Error code of function.
#define st_core_return( function_return_code )  \
	st_sys_record_cur_loc_desc() \
	stLibCore::CoreReturn( function_return_code ); \
	return

/// \brief		Function returns with nothing.
/// \note		Used by void functions.
/// \param[in]	function_return_code Error code of function.
#define st_core_discard( current_status, new_function_name ) \
	st_sys_record_cur_loc_desc() \
	return stLibCore::CoreDiscard( current_status, new_function_name )

/// \brief		Function returns with nothing.
/// \note		Used by void functions.
/// \param[in]	function_return_code Error code of function.
#define st_last_err()  \
	stLibCore::LastErrCode()

/// \brief Get last error description of system API
/// \note  WIN32 supports only so far.
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

	/// \brief Gets a size of heap memory points to.  Others will cause a error.
	/// \param[in] memory Heap memory.
#	define st_sys_heap_memory_size( memory ) \
		je_malloc_usable_size( memory )

	/// \brief  Get memory alloced by assigned method.
	/// \tparam new
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

	/// \brief Gets a size of heap memory points to.  Others will cause a error.
	/// \param[in] memory Heap memory.
#	define st_sys_heap_memory_size( memory ) \
		stLibCore::stCore::HeapSize( memory )

	/// \brief  Get memory alloced by assigned method.
	/// \tparam new
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

	/// \brief Lock code block quickly.
	/// \param[in] code Your code which is needed to be locked.
	/// \param[in] cs   Critical Section
	/// \see stCriticalSection
#	define st_atomic( code, cs ) \
	cs.Lock(); \
	code; \
	cs.Unlock()

#elif defined( ST_SWITCH_MT_SAFE_OFF )
	/// \brief Lock code block quickly.
	/// \param[in] code Your code which is needed to be locked.
	/// \param[in] cs   Critical Section
	/// \see stCriticalSection
#	define st_atomic( code,cs ) \
	code

		   /* !ST_SWITCH_MT_SAFE_OFF */
#endif     /* !ST_SWITCH_MT_SAFE_ON */

/// \}


#endif /* !__STLIB_CORE_H__ */
