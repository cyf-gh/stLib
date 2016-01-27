/*

Base random number class.

WELL512   Quote "https://github.com/9chu/fancy2d/blob/master/fancylib/fcyMisc/fcyRandom.h".
Xorshift  Quote  Marsaglia.

*/
#ifndef __STLIB_RANDOM_H__
#define __STLIB_RANDOM_H__

#include "..\core\Def.h"

namespace stLibUtils {

/***********************************************************************

  Random

***********************************************************************/

class Random {
public:
    virtual un32    GetRandUInt() = 0;

	un32			GetRandUInt( un32 max );
	f32				GetRandFloat();
	f32				GetRandFloat( f32 minBound, f32 maxBound );
};

class stRandomWELL512 : public Random {
private:
    n32				m_state[16];
	n32				m_index;
	n32				m_rdmSeed;

public:
	un32			GetRandUInt();

    un32			GetRandSeed();
	void			SetSeed( un32 seed );

					stRandomWELL512();
					stRandomWELL512( un32 seed );
					~stRandomWELL512();
};

class stRandomXORSHIFT : public Random {
public:
    un32            GetRandUInt();

public:
                    stRandomXORSHIFT();
                    ~stRandomXORSHIFT();
};

} /* stLibUtils */

#endif /* !__STLIB_RANDOM_H__ */

