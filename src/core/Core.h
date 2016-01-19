/*

Provides core error record of stLib.

*/

#ifndef __STLIB_CORE_H__
#define __STLIB_CORE_H__

class stStrW;

#include "Def.h"

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
								~stCore();

public:
	static stFunctionControl *	m_controller;
	static stCurLocDesc	*		m_desc;

	static un32					HeapSize( void *memory );
	static void					CheckPtrNull( void *memory );

	static void					CoreReturn( const stResult returnCode );
	static void					CoreDiscard( const stResult curStatus, const char *newFunctionName );

	static stResult				LastErrCode();
	static void					RecordLocDesc();

	static stStrW				SysLastErrDesc();
};

#ifdef _ST_DEBUG

	static char					s_curLocDesc[ 2048 ];  // info description string.

	/*
	============
	st_sys_record_cur_loc_desc

	Records the current code location detail.
	============
	*/
	#define st_sys_record_cur_loc_desc() \
		st_zero_memory( stLibCore::s_strCurLocDesc, 1 ); \
		sprintf( \
			stLibCore::s_strCurLocDesc, \
			"FILE: %s\nFUNCTION NAME: %s\nLINE: %d\nDATE: %s\nTIME: %s\n", \
			__FILE__, __FUNCTION__, __LINE__, __DATE__, __TIME__ )

#else /* !_ST_DEBUG */

	static char					s_curLocDesc[ 1 ];  // info description string.

	#define st_sys_record_cur_loc_desc();

#endif /* !_ST_RELEASE */

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
	stLibCore::stCore::CoreReturn( function_return_code ) \
	return var_to_return

#define st_core_return( function_return_code )  \
	st_sys_record_cur_loc_desc(); \
	return stLibCore::stCore::CoreReturn( function_return_code )

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

/*
============
st_sys_heap_memory_size

Returns a size of heap memory points to.  Others will cause a error.
============
*/
#define st_sys_heap_memory_size( memory ) \
	stLibCore::stCore::HeapSize( memory )

} /* stLibCore */

#endif /* !__STLIB_CORE_H__ */
