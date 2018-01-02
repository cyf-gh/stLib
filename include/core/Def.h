/**
 *	Defines base stuff of stLib.  This file should be included at the beginning of the program.
 */

#ifndef __STLIB_DEF_H__
#define __STLIB_DEF_H__

#include <cstdint>

/** \defgroup basetype Types Base
 *  Base types defined by stLib.
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

/** \ingroup coremacros
 *  \{
 */

/** \brief		   Set each memory to NULL value.
 *	\param[in] p   Memory pointer.
 *	\param[in] len Length of memory.
 */
#define st_zero_memory( p, len ) \
	memset( p, 0, len )	

/** \brief		      If took error.
 *	\param[in] result Error code.
 */
#define st_do_err( result )	\
	( ( ( stResult ) ( result ) ) < 0 )

/** \brief		   Release a COM object safely.
 *	\param[in out] COM object pointer.
 */
#define st_safe_rel( p ) \
if( p != NULL ) { \
	p->Release(); \
	p = NULL; \
}

/** \brief Force a class to be a non-binary copy class.
 *  \param class_name Name of class.
 */
#define st_class_no_bin_cpy( class_name ) \
public: \
    class_name &operator=( const class_name& rhs ) = delete;

/** \} */ 

#define ST_NOERR				( ( stResult ) 0  )
#define ST_NOERR_INTERNAL		( ( stResult ) 10 )

#include "..\Switch.h"

#include "def\Platform.h"
#include "def\Build.h"


/** \defgroup discard Stuff Discarded
 *  Discarded features.
 *  \{
 */
#ifdef __cplusplus

/** \brief delete a heap memory which alloced by new.
 *	\note  Discarded. 
 *  \see   st_new_class
 */
#	define st_safe_del( p ) \
if ( p != NULL ) { \
	delete p; \
	p = NULL; \
}

/** \brief delete a heap memory which alloced by new.
 *	\note  Discarded. 
 *  \see   st_new_class
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
