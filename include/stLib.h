#pragma once

#include "_stdefs.h"
#include "stString.h"
#include "stStringExtra.h"

#include "stStopwatch.h"
#include "stRandom.h"
#include "stThread.h"

namespace_stLib {

#ifdef ST_ENFORCE_ASCI
	using ST_RESULT = ST_RESULTA;
	using stStr = stStrA;
#	define g_result_null g_result_null_a;
#else
	using ST_RESULT = ST_RESULTW;
	using stStr = stStrW;
#	define g_result_null g_result_null_w;
#endif /* !ST_ENFORCE_ASCI */

}