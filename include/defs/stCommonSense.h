#pragma once

#include "stDef.h"

#define st_make_enum_relative_concept( enum_class_name, A, B ) \
	enum class enum_class_name { \
		A, B, Both, Neither \
	} // enum_class_name

namespace_stLib {
	st_make_enum_relative_concept( ST_FrontOrBack, Front, Back );
	st_make_enum_relative_concept( ST_MinOrMax, Min, Max );
} // stLib
