#pragma once

#include "stDef.h"

#define st_arg_fill bool
#define st_arg_fill_1 st_arg_fill
#define st_arg_fill_2 st_arg_fill, st_arg_fill
#define st_arg_fill_3 st_arg_fill, st_arg_fill, st_arg_fill
#define st_arg_fill_4 st_arg_fill, st_arg_fill, st_arg_fill, st_arg_fill
#define st_arg_fill_5 st_arg_fill, st_arg_fill, st_arg_fill, st_arg_fill, st_arg_fill

#define st_arg_fill_value 0
#define st_arg_fill_value_1 st_arg_fill_value
#define st_arg_fill_value_2 st_arg_fill_value, st_arg_fill_value
#define st_arg_fill_value_3 st_arg_fill_value, st_arg_fill_value, st_arg_fill_value
#define st_arg_fill_value_4 st_arg_fill_value, st_arg_fill_value, st_arg_fill_value, st_arg_fill_value
#define st_arg_fill_value_5 st_arg_fill_value, st_arg_fill_value, st_arg_fill_value, st_arg_fill_value, st_arg_fill_value

namespace_stLib {
template <typename T_Return, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct Traits_GenericFunctions {
	typedef T_Return ( * type_p7Args ) ( T1 a, T2 b, T3 c, T4 d, T5 e, T6 f, T7 g );
	typedef T_Return ( * type_p6Args ) ( T1 a, T2 b, T3 c, T4 d, T5 e, T6 f );
	typedef T_Return ( * type_p5Args ) ( T1 a, T2 b, T3 c, T4 d, T5 e );
	typedef T_Return ( * type_p4Args ) ( T1 a, T2 b, T3 c, T4 d );
	typedef T_Return ( * type_p3Args ) ( T1 a, T2 b, T3 c );
	typedef T_Return ( * type_p2Args ) ( T1 a, T2 b );
	typedef T_Return ( * type_p1Args ) ( T1 a );
	typedef T_Return ( * type_p0Args ) ( void );
};
} // stLib