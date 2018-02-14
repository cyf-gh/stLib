
/// \brief Provides thread features.
#ifndef __STLIB_THREAD_H__
#define __STLIB_THREAD_H__

#include "..\core\Def.h"

/// \addtogroup base
/// \{

/// \brief Thread
class stThread {
private:
	HANDLE              m_thread;
	DWORD               m_threadID;

public:
	static DWORD WINAPI execute(void* p);

protected:
	virtual un32 		ThreadJob() = 0;

public:
	HANDLE 				Handle();
	bool 				Resume();
	bool 				Suspend();
	bool 				Wait( n32 timeLimited = -1 );
	bool 				Terminate( n32 exitCode = -1 );
	un32 				GetExitCode();

public:
						stThread( bool pauseThread = true );
						~stThread();
};

/// \brief Critical section
class stCriticalSection {
private:
    CRITICAL_SECTION    m_section;

public:
    void                Lock();
    bool                TryLock();
    void                Unlock();

                        stCriticalSection();
                        ~stCriticalSection();
};

/// \}

#endif // THREAD_H_INCLUDED
