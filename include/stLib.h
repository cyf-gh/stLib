#pragma once

#include "_stdefs.h"
#include "stString.h"
#include "stStringExtra.h"

#include "stStopwatch.h"
#include "stRandom.h"
#include "stThread.h"
#include "stStream.hpp"
#include "stMaths.h"

namespace_stLib {

#ifdef ST_ENFORCE_ASCI
	using ST_RESULT = ST_RESULTA;
	using stStr = stStrA;
	using stStreamT = stStreamA;
	using stStreamHelperT = stStreamHelperA;
#	define g_result_null g_result_null_a;
#else
	using ST_RESULT = ST_RESULTW;
	using stStr = stStrW;
	using stStreamT = stStreamW;
	using stStreamHelperT = stStreamHelperW;
#	define g_result_null g_result_null_w;
#endif /* !ST_ENFORCE_ASCI */

namespace Math {
	typedef stVec2<un32> stVec2Un32, stPointL, stSizeL;
	typedef stRect<un32> stRectUn32, stRectL;
}

}

#define USING_STLIB using namespace stLib;