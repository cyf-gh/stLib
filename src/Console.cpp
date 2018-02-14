#include "..\include\core\Console.h"
#include "..\include\base\Thread.h"

using namespace stLibCore;
HWND stMain::m_hconsole = NULL;

int stConsoleW::m_argc = 0;
wchar_t **stConsoleW::m_argv = NULL;

int stConsoleA::m_argc = 0;
char **stConsoleA::m_argv = NULL;



un32 stCommand1::ThreadJob() {
	m_isfinishedProcCMD = true; // ³õÊ¼»¯
	
	while( 1 ) {
		if ( m_isfinishedProcCMD ) {
			m_pcs->Lock();
				readCommand();
				CMDProcReady();
			m_pcs->Unlock();
			Suspend();
		} else {
			Suspend();
		}
	}
	st_core_return_success();
}

void stCommand1::readCommand() {
	wchar_t aTmp[100] = { 0 };
	static un32 lastTotalCount = 0;
	lastTotalCount = m_vecCommandArgData.size();
	
	setbuf(stdin, NULL);
	m_data.Clear();
	wprintf( L"\n~>" );// debug
	wscanf( L"%[^\n]%*c", aTmp );
	
	m_data.SetStr( aTmp );
	if ( m_data.IsEmpty() ) {
		return;
	} else {
		m_vecEachCommandArgCount.push_back( m_data.Split( L' ', m_vecCommandArgData ) - lastTotalCount );
		++m_totalCommandCount;
	}
}

stCommand1::stCommand1() : m_isfinishedProcCMD( false ), m_pcs( new stCriticalSection ), m_totalCommandCount( 0 ) { }

stCommand1::~stCommand1() { 
	for ( int i =0; i < m_vecCommandArgData.size(); ++i ) {
		st_safe_del( m_vecCommandArgData.at( i ) );
	}
	st_safe_del( m_pcs );
}
