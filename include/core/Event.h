#ifndef __STLIB_EVENT_H__
#define __STLIB_EVENT_H__

namespace __stLibEvent { }

#define ST_EVENT_START_IMPL namespace __stLibEvent {
#define ST_EVENT_END_IMPL						   }

/*
	Declares a event type.
	Uses between ST_EVENT_START_IMPL and ST_EVENT_END_IMPL.

Sample :

ST_EVENT_DECLARE( EventSample, void, ( un32 p1, char p2 ) )

*/
#define ST_EVENT_DECLARE( typedef_name, return_type, params ) \
	typedef return_type ( *typedef_name )params;

/*

	Implements a instance of an event.
	Uses between a namespace.

Sample :

namespace XXX {
	ST_EVENT( EventSample ) pSample = NULL;
}

*/
#define ST_EVENT( typedef_name ) \
	__stLibEvent::typedef_name

/*

	Call an event function.
	NULL is acceptable.

Sample :

ST_CALL_EVENT( pSample, ( number1, string2 ) );

*/
#define ST_CALL_EVENT( function_ptr, params ) \
	if ( function_ptr ) \
		( *function_ptr )params\

#endif /* !__STLIB_EVENT_H__ */