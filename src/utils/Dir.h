/*

Base direction class.  Provides base paths processions.

*/

#ifndef __STLIB_PATHHELPER_H__
#define __STLIB_PATHHELPER_H__

#include "..\core\Def.h"
#include "..\core\Core.h"
#include "..\core\ErrCode.h"
#include "..\base\Str.h"

namespace stLibUtils {

/***********************************************************************

  stDir

***********************************************************************/

class stDir {

private:
    stStrW              m_curPath;

public:
	stStrW 			    Cur() const { return m_curPath; };
    stDir &             SetCur( const stStrW &dir );
	stDir &			    Root();
	stDir &             Cd( const stStrW &lower );
	stDir &             CdUp();
	stDir &				Mkdir();
	stDir &				Rmdir();
    stStrW              DirName();
	bool				IsExist();
	bool				IsExist( const stStrW &lower );
	void				Ls( std::vector<stStrW> &fileList );

                        stDir( const stStrW &root );
                        stDir();
	virtual             ~stDir();
};

} /* stLibUtils */

#endif /* !__STLIB_PATHHELPER_H__ */
