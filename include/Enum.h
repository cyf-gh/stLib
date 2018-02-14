
/// \brief The enumerations of stLib.
#ifndef __STLIB_ENUM_H__
#define __STLIB_ENUM_H__

#include <stdio.h>

namespace stLibEnum {

/// \addtogroup Enumerations
/// \{

/// \brief File open modes.
enum FILEOPENMODE {
	ST_NOMODE				= 0,
	// Binary
	ST_WRITE_BINARY			= 1,
	ST_READ_BINARY			= 2,
	ST_CREATE_BINARY		= 3,
	// ASCI
	ST_WRITE_ASCI			= 7,
	ST_READ_ASCI			= 8,
	ST_CREATE_ASCI			= 9,
	// Unicode
	ST_WRITE_UNICODE		= 4,
	ST_READ_UNICODE			= 5,
	ST_CREATE_UNICODE		= 6,
	// UTF-8
	ST_WRITE_UTF8			= 10,
	ST_READ_UTF8			= 11,
	ST_CREATE_UTF8			= 12
};

/// \brief File positions.
enum FILEPOSITIONORG {
	ST_CUR					= SEEK_CUR,
	ST_END					= SEEK_END,
	ST_HEAD					= SEEK_SET
};

/// \brief String trim modes.
enum TRIMMODE {
	TM_BOTH_SIDE,
	TM_LEFT,
	TM_RIGHT
};

enum CORERETURN {
	ST_CR_WARNNING,
	ST_CR_ERROR
};

/// \}

} /* stLibEnum */

#endif /* !__STLIB_ENUM_H__ */
