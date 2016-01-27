/*

Defines internal error codes.

*/
#ifndef __STLIB_ERRCODE_H__
#define __STLIB_ERRCODE_H__

namespace stLibErrCode {

enum GLOBAL {
	ST_ERR_UNKNOWN = -25
};

/***********************************************************************

  IO Steam Errs.
  [ -1, -19 ]

***********************************************************************/
enum STREAMERRS {
	ST_ERR_UNKNOWNOPENMODE 		= -18,
	ST_ERR_NULLFILEHANDLE 		= -1,
	ST_ERR_CREATECLONEFILE      = -25,
	ST_ERR_CLOSECLONEFILE		= -26,
	ST_ERR_OPENFILEHANDLE 		= -4,
	ST_ERR_OPENEDFILEHANDLE 	= -3,
	ST_ERR_CLOSEFILE 			= -2,
	ST_ERR_SEEK 				= -13,
	ST_ERR_FLUSHFILE 			= -5,
	ST_ERR_OUTOFSIZE 			= -6,
	ST_ERR_NULLDATAPARAM 		= -11,
	ST_ERR_UNABLEWRITE 			= -8,
	ST_ERR_UNABLEREAD 			= -9,
	ST_ERR_NULLSTREAMHANDLE 	= -19,
	ST_ERR_READBYTE 			= -7,
	ST_ERR_WRITEBYTE 			= -10,
	ST_ERR_READTEXT 			= -16,
	ST_ERR_WRITETEXT 			= -15
}; 

/***********************************************************************

  Directory Errs.
  [ -20, -19 ]

***********************************************************************/
enum DIRERRS {
	ST_ERR_LS 					= -20,
	ST_ERR_MKDIR 				= -21,
	ST_ERR_RMDIR 				= -22,
	ST_ERR_GETROOTDIR		    = -23,
};

enum MEMORYPOOLERRS {
	ST_ERR_FREEANONBELONGNINGMEM = -24
};

} /* stLibErrCode */

#endif /* !__STLIB_ERRCODE_H__ */