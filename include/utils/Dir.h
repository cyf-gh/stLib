
/// \brief Base direction class.  Provides base paths processions.
#ifndef __STLIB_PATHHELPER_H__
#define __STLIB_PATHHELPER_H__

#include "..\core\Def.h"
#include "..\core\Core.h"
#include "..\core\ErrCode.h"
#include "..\base\Str.h"

namespace stLibUtils {
/// \addtogroup utils
/// \{

/// \class stDir
/// \brief Base path processing.
class stDir {

    st_class_no_bin_cpy( stDir )

private:
    stStrW m_curPath;

public:
	stStrW Cur() const { return m_curPath; }; ///< \brief Get current path string.

	/// \brief		   Set current path.
	/// \param[in] dir New dir.
	/// \return		   this pointer.
    stDir &SetCur( const stStrW &dir );

	/// \brief Gets Root path of current running application.
	/// \return	exe path.  Do not include the exe file name.
	/// \return		   this pointer.
	stDir &Root();

	/// \brief			 Enters the lower folder.
	/// \param[in] lower Lower folder name.
	/// \note			 No error-occurring method.
	/// \return			 this pointer.
	stDir &Cd( const stStrW &lower );

	/// \brief  Enters upper folder.
	/// \note   No error-occurring method.
	/// \return	this pointer
	stDir &CdUp();

	/// \brief  Creates directory with current dir string.
	///		    Will crash if dir is not existed, with ST_ERR_MKDIR.  Check IsExist() before it.
	/// \return this pointer.
	stDir &Mkdir();
	
	/// \brief  Removes directory with current dir string.
	/// \note   If there's a error,  st_last_err()
	///		    Will crash if dir is not existed, with ST_ERR_RMDIR.  Check IsExist() before it.
	/// \return this pointer.
	stDir &Rmdir();

	/// \brief	Gets current dir string.
	/// \return dir string.
    stStrW DirName();

	/// \brief  Checks if current dir exists.
	bool IsExist();

	/// \brief			 Detects if the lower dir exists.
	/// \param[in] lower Lower folder name.
	bool IsExist( const stStrW &lower );

	/// \brief Enumerates all stuffs in current dir.
	/// \note  Ignores '.' and '..' paths. \n
	///		   Will crash if dir is not existed, with ST_LS.  Check IsExist() before it.
	/// \param[in out] fileList A list to get all file names.
	void Ls( std::vector<stStrW> &fileList );

	/// \brief		Constructor.
	/// \param[in]	root Original dir.
    stDir( const stStrW &root );

    /// \brief Constructor.
	stDir();

	/// \brief Destructor.
	virtual ~stDir();
};
/// \}

} /* stLibUtils */

#endif /* !__STLIB_PATHHELPER_H__ */
