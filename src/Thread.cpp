#include "..\include\stThread.h"

using namespace stLib;

/*
==============================================================

	stThread

==============================================================
*/

/*
============
stThread::stThread
============
*/
stThread::stThread( bool pauseThread  ) {
	m_thread = CreateThread( 0, 0, &execute, ( void* )this, pauseThread ? CREATE_SUSPENDED : 0, &m_threadID );
	if ( m_thread == NULL ) {
		throw "CreateThread Failed.";
	}
}

/*
============
stThread::~stThread
============
*/
stThread::~stThread() {
	CloseHandle( m_thread );
}

/*
============
stMemPool::execute
============
*/
DWORD WINAPI stThread::execute( void *p ) {
	return ( ( stThread * )p )->ThreadJob();
}

/*
============
stThread::Handle
============
*/
HANDLE stThread::Handle() {
	return m_thread;
}

/*
============
stThread::Resume
============
*/
bool stThread::Resume() {
	return ResumeThread( m_thread ) != ( DWORD ) - 1;
}

/*
============
stThread::Suspend
============
*/
bool stThread::Suspend() {
	return SuspendThread( m_thread ) != ( DWORD ) - 1;
}

/*
============
stThread::Wait
============
*/
bool stThread::Wait( n32 timeLimited ) {
	return WaitForSingleObject( m_thread, timeLimited ) != ( DWORD ) - 1;
}

/*
============
stThread::Terminate
============
*/
bool stThread::Terminate( n32 exitCode ) {
	return TerminateThread( m_thread, exitCode ) != false;
}

/*
============
stThread::GetExitCode
============
*/
un32 stThread::GetExitCode() {
	DWORD code = ( DWORD )-1;
	GetExitCodeThread( m_thread, &code );
	return code;
}

/*
==============================================================

	stCriticalSection

==============================================================
*/

/*
============
stCriticalSection::stCriticalSection
============
*/
stCriticalSection::stCriticalSection() {
	InitializeCriticalSection( &m_section );
}

/*
============
stCriticalSection::~stCriticalSection
============
*/
stCriticalSection::~stCriticalSection() {
	DeleteCriticalSection( &m_section );
}

/*
============
stCriticalSection::TryLock
============
*/
bool stCriticalSection::TryLock() {
	return TryEnterCriticalSection( &m_section ) != FALSE;
}

/*
============
stCriticalSection::UnLock
============
*/
void stCriticalSection::Unlock() {
	LeaveCriticalSection( &m_section );
}

/*
============
stCriticalSection::Lock
============
*/
void stCriticalSection::Lock() {
	EnterCriticalSection( &m_section );
}