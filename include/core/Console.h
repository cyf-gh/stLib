/// \main函数参数输入
#pragma once

#include "Def.h"
#include "Core.h"
#include "ErrCode.h"
#include "..\include\base\Thread.h"
#include "..\include\base\Str.h"

class stThread;
class stCriticalSection;

namespace stLibCore {

class stMain {
public:
	
	st_class_no_bin_cpy( stMain );

protected:
	static HWND m_hconsole;

public:
	static HWND GetConsoleHandle() { return m_hconsole; }
	static void ShowConsole( bool isShow ) { 
		int show = ( isShow ) ? SW_SHOW : SW_HIDE; 
		ShowWindow( m_hconsole, show );	
	}
};

}

class stConsoleA : public stLibCore::stMain {
public:
	
	st_class_no_bin_cpy( stConsoleA );

	static void Init( int argc, char **argv, const char *SetTitle ) {
		m_hconsole = GetConsoleWindow();
		stConsoleA::m_argc = argc; stConsoleA::m_argv = argv;

		stConsoleA::SetTitle( SetTitle );
	}
	static void SetTitle( const char *strtitle = NULL ) { 
		strtitle = ( strtitle == NULL ) ? "" : strtitle;
		SetConsoleTitleA( strtitle );		
	}
	static int GetArgCount() { return m_argc; }
	static char *GetArgAt( const int index ) { 
		if ( !( index > 0 && index < m_argc ) ) {
			st_core_return_with_var( stLibErrCode::ST_ERR_ARGUOUTOFRANGE, NULL );
		}
		return m_argv[index]; 
	}

private:
	static int m_argc;
	static char **m_argv;
};

class stConsoleW : public stLibCore::stMain {
public:

	st_class_no_bin_cpy( stConsoleW );

	static void Init( int argc, wchar_t **argv, const wchar_t *strtitle = NULL) {
		m_hconsole = GetConsoleWindow();
		stConsoleW::m_argc = argc; stConsoleW::m_argv = argv;
	
		stConsoleW::SetTitle( strtitle );
	}
	static void SetTitle( const wchar_t *strtitle = NULL ) { 
		strtitle = ( strtitle == NULL ) ? L"" : strtitle;
		SetConsoleTitleW( strtitle );		
	}
	static int GetArgCount() { return m_argc; }
	static wchar_t *GetArgAt( const int index ) { 
		if ( !( index >= 0 && index < m_argc ) ) {
			st_core_return_with_var( stLibErrCode::ST_ERR_ARGUOUTOFRANGE, NULL );
		}
		return m_argv[index]; 
	}

private:
	static int m_argc;
	static wchar_t **m_argv;
};

class stCommand1 : public stThread {
private:
	stCriticalSection *m_pcs;
	void CMDProcFinished() { m_isfinishedProcCMD = true; }
	void CMDProcReady() { m_isfinishedProcCMD = false; }
	bool IsReadyToProcCMD() { 	return ( m_isfinishedProcCMD == false ); }
	un32 ThreadJob();

private:	
	bool m_isfinishedProcCMD;
	void readCommand();
	stStrW m_data;
	un32 m_totalCommandCount;

public:
	bool Start() { return Resume(); }
	bool Pause() { return Suspend(); }
	void LockCS() { m_pcs->Lock(); }
	void UnlockCS() { m_pcs->Unlock(); }
	void ProcFinished() { CMDProcFinished(); }
	bool IsFinishedRead() { return IsReadyToProcCMD(); }
	un32 GetTotalCommandCount() const { return m_totalCommandCount; }

	/// \brief 所有的命令参数数据
	std::vector<stStrW *> m_vecCommandArgData;
	/// \brief 每一行命令的参数数量
	/// \see GetTotalCommandCount()
	std::vector<un32> m_vecEachCommandArgCount;

	stCommand1();
	virtual ~stCommand1();
};

#define ST_CMD_1_LOOP( tcmd1, cmd_process_function ) \
	if ( tcmd1->IsFinishedRead() ) { \
		tcmd1->LockCS(); \
		cmd_process_function; \
		tcmd1->ProcFinished(); \
		tcmd1->UnlockCS(); \
		tcmd1->Start(); \
	}
				

/*
if ( s_testcmd.IsReadyToProcCMD() ) {
	s_testcmd.m_pcs->Lock();
	wprintf( L"Finished proc\n\n" );
	s_testcmd.CMDProcFinished();
	s_testcmd.m_pcs->Unlock();
	s_testcmd.Resume();
}
*/

#ifdef ST_SWITCH_STR_UNICODE

#	define stConsoleT	stConsoleW	

#elif defined( ST_SWITCH_STR_ASCI )

#	define stConsoleT	stConsoleA	

#endif // 定义T字符