/*

stLib feature switches.

*/
#ifndef __STLIB_SWITCH_H__
#define __STLIB_SWITCH_H__


/***********************************************************************

    Switches

***********************************************************************/
   #define                 ST_SWITCH_JEMALLOC_ON		// use jemalloc memory management
// #define				   ST_SWITCH_MEMORYPOOL_ON		// use stLib memory pool memory management
// #define				   ST_SWITCH_MEMORYPOOL_OFF		// use general memory management

   #define				   ST_SWITCH_MT_SAFE_ON			// use multi-thread safely operations
// #define				   ST_SWITCH_MT_SAFE_OFF		// use no multi-thread safely operations

#endif /* !__STLIB_SWITCH_H__ */