/*

Base stop watch class.  Provides high-precision stop watch.

Quote : "https://github.com/9chu/fancy2d/blob/master/fancylib/fcyMisc/fcyRandom.h"

*/

#ifndef __STLIB_STOPWATCH_H__
#define __STLIB_STOPWATCH_H__

#include "..\core\Def.h"

namespace stLibUtils {

/***********************************************************************

  StopWatch

***********************************************************************/

class stStopWatch {
private:
	n64							m_freq;
	n64							m_last;
	n64							m_fixStart;
	n64							m_fixAll;

public:
	void						Pause();
	void						Resume();
	void						Reset();
	f64							GetElapsed();

public:
								stStopWatch();
								~stStopWatch();
};

} /* stLibUtils */

#endif /* !__STLIB_STOPWATCH_H__ */
