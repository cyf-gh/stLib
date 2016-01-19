#include "Random.h"

using namespace stLibUtils;

/*
==============================================================

	Random features

==============================================================
*/

/*
============
Random::GetRandUInt
============
*/
un32 Random::GetRandUInt( un32 max ) {
	return GetRandUInt() % ( max + 1 );
}

/*
============
Random::GetRandFloat
============
*/
f32 Random::GetRandFloat() {
	return GetRandUInt( 1000000 ) / 1000000.f;
}

/*
============
Random::GetRandFloat
============
*/
f32 Random::GetRandFloat( f32 minBound, f32 maxBound ) {
	return GetRandFloat() * ( maxBound - minBound ) + minBound;
}

/*
==============================================================

	WELL512

==============================================================
*/

/*
============
stRandomWELL512::stRandomWELL512
============
*/
stRandomWELL512::stRandomWELL512() {
	SetSeed( GetTickCount() );
}

stRandomWELL512::stRandomWELL512( un32 seed ) {
	SetSeed( seed );
}

/*
============
stRandomWELL512::~stRandomWELL512
============
*/
stRandomWELL512::~stRandomWELL512() { }

/*
============
stRandomWELL512::GetRandSeed
============
*/
un32 stRandomWELL512::GetRandSeed()  {
	return m_rdmSeed;
}

/*
============
stRandomWELL512::GetRandUInt
============
*/
un32 stRandomWELL512::GetRandUInt() {
	un32 a, b, c, d;
	a = m_state[ m_index ];
	c = m_state[ ( m_index + 13 ) & 15 ];
	b = a ^ c ^ ( a << 16 ) ^ ( c << 15 );
	c = m_state[ ( m_index+ 9 ) & 15 ];
	c ^= ( c >> 11 );
	a = m_state[ m_index ] = b ^ c;
	d = a ^ ( ( a << 5 ) & 0xDA442D24UL );
	m_index= ( m_index+ 15 ) & 15;
	a = m_state[ m_index ];
	m_state[ m_index ] = a ^ b ^ d ^ ( a << 2 ) ^ ( b << 18 ) ^ ( c << 28 );
	return m_state[ m_index ];
}

/*
============
stRandomWELL512::SetSeed

WELL512.
============
*/
void stRandomWELL512::SetSeed( un32 seed ) {
	const un32 mask = ~0u;

	m_rdmSeed = seed;
	m_index = 0;
	m_state[ 0 ] = seed & mask;
	for ( un32 i = 1; i < 16; ++i ) {
		m_state[i] = ( 1812433253UL * ( m_state[ i - 1 ] ^ ( m_state[ i - 1 ] >> 30 ) ) + i ) & mask;
	}
}

/*
==============================================================

	Xorshift

==============================================================
*/

/*
============
stRandomXORSHIFT::stRandomXORSHIFT
============
*/
stRandomXORSHIFT::stRandomXORSHIFT() { }

/*
============
stRandomXORSHIFT::~stRandomXORSHIFT
============
*/
stRandomXORSHIFT::~stRandomXORSHIFT() { }

/*
============
stRandomXORSHIFT::GetRandUInt

Xorshift.
============
*/
un32 stRandomXORSHIFT::GetRandUInt() {
    static un32 x = 123456789;
    static un32 y = 362436069;
    static un32 z = 521288629;
    un32 t;

    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;

    t = x;
    x = y;
    y = z;
    z = t ^ x ^ y;

    return z;
}
