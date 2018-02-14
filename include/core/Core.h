
/// \brief �������
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

static bool s_IsDebugMode = true; // ������

static ch8	s_curLocDesc[ 2048 ];  // ��ǰ����λ�õ�����

} /* stLibCore */


/// \defgroup ���Ĳ����궨��
/// \brief ��ײ������صĺ궨��
/// \{

#ifdef         ST_SWITCH_ISDEBUGMODE_ON
/// \brief ��¼��ǰ����������Ϣ
/// \note  ���԰汾��s_IsDebugMode�������ã�����ʹ��ST_SWITCH_ISDEBUGMODE_ON�����ô˹���
#	define st_sys_record_cur_loc_desc() \
	if ( stLibCore::s_IsDebugMode ) { \
		st_zero_memory( stLibCore::s_curLocDesc, 1 ); \
		sprintf( \
			stLibCore::s_curLocDesc, \
			"FILE: %s\nFUNCTION NAME: %s\nLINE: %d\nDATE: %s\nTIME: %s\n", \
			__FILE__, __FUNCTION__, __LINE__, __DATE__, __TIME__ ); \
	}
#elif defined( ST_SWITCH_ISDEBUGMODE_OFF )
/// \brief ��¼��ǰ����������Ϣ
/// \note  ���а汾��s_IsDebugMode�������ã�����ʹ��ST_SWITCH_ISDEBUGMODE_ON�����ô˹���
#	define st_sys_record_cur_loc_desc()
// to do nothing
#endif

/// \brief		���һ��ָ���Ƿ�Ϊ��
/// \param[in]	ָ��
#define st_check_null_ptr( memory ) \
	st_sys_record_cur_loc_desc() \
	stLibCore::CheckPtrNull( memory )

/// \brief		��������һ��ֵ
/// \note		���ڷ�void����
/// \param[in]	function_return_code ��ǰ���������մ������
/// \param[in]	var_to_return		 ��ǰ�����ķ���ֵ
#define st_core_return_with_var( function_return_code, var_to_return ) \
	st_sys_record_cur_loc_desc() \
	stLibCore::CoreReturn( function_return_code ); \
	return var_to_return

/// \brief		��������һ��ֵ
/// \note		���ڷ�void���������մ������Ӧ����ST_NOERR�Ҳ�������ش������������������õĴ������
/// \param[in]	function_return_code ��ǰ���������մ�����룬�Ҳ���ΪST_NOERR������ش�������
/// \param[in]	var_to_return		 ��ǰ�����ķ���ֵ
#define st_core_return_with_var_with_warnningcode( function_return_code, var_to_return ) \
	st_sys_record_cur_loc_desc() \
	stLibCore::CoreReturn( function_return_code, true ); \
	return var_to_return

/// \brief		�����������κ�ֵ
/// \note		����void����
/// \param[in]	function_return_code ��ǰ���������մ������
#define st_core_return( function_return_code )  \
	st_sys_record_cur_loc_desc() \
	stLibCore::CoreReturn( function_return_code ); \
	return

/// \brief		����������
/// \note		��ʾ����������
/// \param[in]	current_status ��ǰ����״̬
/// \param[in]	new_function_name ��ʾ�º����ĺ���ǩ��
#define st_core_discard( current_status, new_function_name ) \
	st_sys_record_cur_loc_desc() \
	stLibCore::CoreDiscard( current_status, new_function_name )

#define st_core_return_success() \
	return ST_NOERR

/// \brief		���ؼ�¼�����һ������
#define st_last_err()  \
	stLibCore::LastErrCode()

/// \brief		��ȡϵͳAPI�Ĵ�����Ϣ
/// \note		����ǰ��֧��WIN32��
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

#ifndef __STLIB_CORE_H_JEMALLOCINFOPRINTED //���ڿ���̨���һ��jemalloc��Ȩ��Ϣ
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

	/// \brief		��ȡ���ڴ��С
	/// \note		��jemalloc�汾��
	/// \param[in]	memory ���ڴ�ָ��
#	define st_sys_heap_memory_size( memory ) \
		je_malloc_usable_size( memory )

	/// \brief		�����������ڴ�ռ�
	/// \note		�������������
	/// \param[in]  T ����
	/// \param[in]	objNum �����С�������͵ĸ���Ϊ��С��λ
	template<typename T>
	ST_INLINE static T *st_new( un64 objNum ) {
		return ( T * )je_malloc( objNum * sizeof( T ) );
	}

	/// \brief		���䵥�����ʹ�С�Ŀռ�
	/// \note		�������������
	/// \param[in]  T ����
	template<typename T>
	ST_INLINE static T *st_new() {
		return ( T * )je_malloc( 1 * sizeof( T ) );
	}

	/// \brief		�ͷŷ�����ڴ�ռ�
	/// \note		�����������ͷţ������ͷ��������ڴ�ռ�
	/// \param[in]  T ����
	/// \param[in]  pt ָ���ַ
	template<typename T>
	ST_INLINE static void st_delete( T **pt ) {
		je_free( *pt );
	}

	/// \brief		�ͷŷ�����ڴ�ռ�
	/// \note		�����������ͷţ������ͷŵ������ڴ�ռ�
	/// \param[in]  T ����
	/// \param[in]  pt ָ���ַ
	template<typename T>
	ST_INLINE static void st_delete_arr( T **pt ) {
		je_free( *pt );
	}

	/// \brief		��������ڴ�ռ�
	/// \warning	������ʹ�ã�COM�����ӿڶ�����Ұָ������	
	/// \param[in]  T ����
	/// \param[in]  instance T���͵�ʵ�����ð�����ʼ�����������ڽ�Ϊ����������ע�����ô������⣡
	template<typename T>
	ST_INLINE static T *st_new_class( const T& instance ) {
		T * const mem = ( T * )( je_malloc( 1 * sizeof( T ) ) );
		memcpy( mem, &instance, sizeof( T ) );
		return mem;
	}

	/// \brief		�ͷ�����ڴ�ռ�
	/// \warning	������ʹ��
	/// \param[in]  T ����
	/// \param[in]  pt ָ���ַ
	template<typename T>
	ST_INLINE static void st_delete_class( T **pt ) {
		( *pt )->~T();
		je_free( ( void * )( *pt ) );
	}

#elif defined( ST_SWITCH_MEMORYPOOL_OFF )
#	pragma message( "Target Switch:[ MEMORY POOL ] : OFF" )
	/// \brief ���ݱ���

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

	/// \brief �������������
	/// \param[in] code ��Ҫ�����Ĵ����
	/// \param[in] cs   �ٽ�����
	/// \see stCriticalSection
#	define st_atomic( code, cs ) \
	cs.Lock(); \
	code; \
	cs.Unlock()

#elif defined( ST_SWITCH_MT_SAFE_OFF )
	/// \brief ���ݱ���
#	define st_atomic( code,cs ) \
	code

		   /* !ST_SWITCH_MT_SAFE_OFF */
#endif     /* !ST_SWITCH_MT_SAFE_ON */

#define ST_CORE_FORECE_SINGLE_INSTANCE_WIN32__BEGIN( uniID ) \
	HANDLE __h_st_single_instance_mutex__ = CreateMutex( NULL, false, uniID );\
	if ( GetLastError() == ERROR_ALREADY_EXISTS ) { \
		CloseHandle( __h_st_single_instance_mutex__ );

#define ST_CORE_FORECE_SINGLE_INSTANCE_WIN32__END() }

/** һ����򵥵�����
	ST_CORE_FORECE_SINGLE_INSTANCE_WIN32__BEGIN( "uniID" ) {
		return 0;
	}
	ST_CORE_FORECE_SINGLE_INSTANCE_WIN32__END();
*/

/// \}


#endif /* !__STLIB_CORE_H__ */
