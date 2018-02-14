/// \brief stLib feature switches.
#ifndef __STLIB_SWITCH_H__
#define __STLIB_SWITCH_H__


/***********************************************************************

    Switches

***********************************************************************/
// #define                 ST_SWITCH_JEMALLOC_ON		/// use jemalloc memory management
// #define				   ST_SWITCH_MEMORYPOOL_ON		/// use stLib memory pool memory management（不可使用）
   #define				   ST_SWITCH_MEMORYPOOL_OFF		/// use general memory management

   #define				   ST_SWITCH_MT_SAFE_ON			/// use multi-thread safely operations
// #define				   ST_SWITCH_MT_SAFE_OFF		/// use no multi-thread safely operations
   
	#define				   ST_SWITCH_ISDEBUGMODE_ON	_ST_DEBUG	/// turn on debug mode
// #define				   ST_SWITCH_ISDEBUGMODE_OFF _ST_RELEASE	/// turn off debug mode

	#define				   ST_SWITCH_STR_UNICODE		/// unicode字符集
// #define				   ST_SWITCH_STR_ASCI			/// asci字符集

#endif /* !__STLIB_SWITCH_H__ */