#include "Dir.h"

using namespace stLibErrCode;
using namespace stLibUtils;

/*
============
stDir::stDir
============
*/
stDir::stDir( const stStrW &root ) : m_curPath( root ) { }

stDir::stDir() {
     Root();
}

/*
============
stDir::~stDir
============
*/
stDir::~stDir() { }

/*
============
stDir::IsExist
============
*/
bool stDir::IsExist() {
	WIN32_FIND_DATAW findData;
    bool 			 isExist = false;
    HANDLE 			 hfind   = FindFirstFileW( m_curPath.Data(), &findData );

    isExist = ( hfind != INVALID_HANDLE_VALUE) && ( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) ?
			  true : false;

    FindClose( hfind );
    return isExist;
}

bool stDir::IsExist( const stStrW &lower ) {
	stStrW 			orgDir( m_curPath );
	bool   			isExist = false;

	m_curPath.Append( L"\\" ).Append( lower );
	isExist = IsExist();
	m_curPath = orgDir;
	return isExist;
}

/*
============
stDir::SetCur
============
*/
stDir &stDir::SetCur( const stStrW &dir ) {
	m_curPath = dir;
	return *this;
}

/*
============
stDir::Root

Returns exe path.  Do not include the exe file name.
============
*/
stDir &stDir::Root() {
	wchar_t path[ MAX_PATH ] = { 0 };

	if( 0 == GetModuleFileNameW( NULL, path, MAX_PATH ) ) {
		st_core_return_with_var( ST_ERR_GETROOTDIR, *this );
	}
	m_curPath.SetStr( path );
	m_curPath.TrimBack( L'\\' );
	return *this;
}

/*
============
stDir::Cd
============
*/
stDir &stDir::Cd( const stStrW &lower ) {
    m_curPath.Append( L"\\" ).Append( lower );
	return *this;
}

/*
============
stDir::CdUp
============
*/
stDir &stDir::CdUp() {
    m_curPath.TrimBack( L'\\' );
    return *this;
}

/*
============
stDir::DirName
============
*/
stStrW stDir::DirName() {
    stStrW dirName( m_curPath );
    un32   times = dirName.RepTimesOf( L'\\' ) - 1;

    dirName.TrimFont( L'\\', times );
    dirName.TrimSingle( stLibEnum::TM_LEFT ); // trim '\'
    return dirName;
}

/*
============
stDir::Mkdir
============
*/
stDir &stDir::Mkdir() {
	if ( 0 == CreateDirectoryW( m_curPath.Data(), 0 ) ) {
		st_core_return_with_var( ST_ERR_MKDIR, *this );
	}
	return *this;
}

/*
============
stDir::Rmdir
============
*/
stDir &stDir::Rmdir() {
	if ( 0 == RemoveDirectoryW( m_curPath.Data() ) ) {
		st_core_return_with_var( ST_ERR_RMDIR, *this );
	}
	return *this;
}

/*
============
stDir::Ls

Ignores '.' and '..' paths.
============
*/
void stDir::Ls( std::vector<stStrW> &fileList ) {
	WIN32_FIND_DATAW  findData;
	HANDLE			  hFileFind;

	st_zero_memory( &findData, sizeof( WIN32_FIND_DATAW ) );
	if ( FAILED( hFileFind = FindFirstFileW( m_curPath.Data(), &findData ) ) ) {
		st_core_return( ST_ERR_LS );
	}
	while( FindNextFileW( hFileFind, &findData ) ) {
		if( wcscmp( findData.cFileName, L"." ) || wcscmp( findData.cFileName, L".." ) ) {
			continue;
		}
		stStrW strPath( m_curPath );
		strPath.Append( findData.cFileName );
		fileList.push_back( strPath );
	}
}
