#ifndef __STLIB_EVENT_H__
#define __STLIB_EVENT_H__

namespace __stLibEvent { }

/// \addtogroup coremacros
/// \{

#define ST_EVENT_START_IMPL namespace __stLibEvent {
#define ST_EVENT_END_IMPL						   }

/// \brief Declares a event type.\n
///		   Uses between ST_EVENT_START_IMPL and ST_EVENT_END_IMPL.
/// \sample \n
///
/// ST_EVENT_DECLARE( EventSample, void, ( un32 p1, char p2 ) )
#define ST_EVENT_DECLARE( typedef_name, return_type, params ) \
	typedef return_type ( *typedef_name )params;

/// \brief Implements a instance of an event. \n
///		   Uses between a namespace.
/// \sample \n
/// namespace XXX { \n
///		ST_EVENT( EventSample ) pSample = NULL; \n
/// } \n
#define ST_EVENT( typedef_name ) \
	__stLibEvent::typedef_name

/// \brief Call an event function.
///		   NULL is acceptable.
/// \sample \n
/// ST_CALL_EVENT( pSample, ( number1, string2 ) );
#define ST_CALL_EVENT( function_ptr, params ) \
	if ( function_ptr ) \
		( *function_ptr )params\

/// \}

#endif /* !__STLIB_EVENT_H__ */