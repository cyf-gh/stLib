#include "..\include\stStopwatch.h"

using namespace stLibUtils;

/*
============
stStopWatch::stStopWatch
============
*/
stStopWatch::stStopWatch() {
	QueryPerformanceFrequency( ( LARGE_INTEGER * ) & m_freq );
	Reset();
}

/*
============
stStopWatch::~stStopWatch
============
*/
stStopWatch::~stStopWatch() { }

/*
============
stStopWatch::Pause
============
*/
void stStopWatch::Pause() {
	QueryPerformanceCounter( ( LARGE_INTEGER * ) & m_fixStart );
}

/*
============
stStopWatch::Resume
============
*/
void stStopWatch::Resume() {
	INT64	now;
	QueryPerformanceCounter( ( LARGE_INTEGER* ) & now );
	m_fixAll += now - m_fixStart;
}

/*
============
stStopWatch::Reset
============
*/
void stStopWatch::Reset() {
	m_fixAll = 0;
	QueryPerformanceCounter( ( LARGE_INTEGER * ) & m_last );
}

/*
============
stStopWatch::GetElapsed
============
*/
f64 stStopWatch::GetElapsed() {
	INT64	now;
	QueryPerformanceCounter( ( LARGE_INTEGER * ) & now );
	return ( ( f64 ) ( now - m_last - m_fixAll ) ) / ( ( f64 ) m_freq );
}
