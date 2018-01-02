
/// \brief Defines internal error codes.
#ifndef __STLIB_ERRCODE_H__
#define __STLIB_ERRCODE_H__

namespace stLibErrCode {

/// \addtogroup errcode Error Codes
/// \{

///\brief Stom global errors. \n
///		  [ -1, -10 ]
enum GLOBAL {
	ST_ERR_UNKNOWN				= -1,
	ST_ERR_NOTFOUND				= -2,
	ST_ERR_INVALIDPARAM			= -3
};

///\brief IO Steam errors.
///		  [ -11, -28 ]
enum STREAMERRS {
	ST_ERR_UNKNOWNOPENMODE 		= -11,
	ST_ERR_NULLFILEHANDLE 		= -12,
	ST_ERR_CREATECLONEFILE      = -13,
	ST_ERR_CLOSECLONEFILE		= -14,
	ST_ERR_OPENFILEHANDLE 		= -15,
	ST_ERR_OPENEDFILEHANDLE 	= -16,
	ST_ERR_CLOSEFILE 			= -17,
	ST_ERR_SEEK 				= -18,
	ST_ERR_FLUSHFILE 			= -19,
	ST_ERR_OUTOFSIZE 			= -20,
	ST_ERR_NULLDATAPARAM 		= -21,
	ST_ERR_UNABLEWRITE 			= -22,
	ST_ERR_UNABLEREAD 			= -23,
	ST_ERR_NULLSTREAMHANDLE 	= -24,
	ST_ERR_READBYTE 			= -25,
	ST_ERR_WRITEBYTE 			= -26,
	ST_ERR_READTEXT 			= -27,
	ST_ERR_WRITETEXT 			= -28
}; 

///\brief  Directory errors.
///		   [ -29, -32 ]
enum DIRERRS {
	ST_ERR_LS 					= -29,
	ST_ERR_MKDIR 				= -30,
	ST_ERR_RMDIR 				= -31,
	ST_ERR_GETROOTDIR		    = -32,
};

#ifdef ST_SWITCH_MEMORYPOOL_ON

///\brief  Memory pool errors.
///		   {-33}
enum MEMORYPOOLERRS {
	ST_ERR_FREEANONBELONGNINGMEM = -33
};

#endif /* !ST_SWITCH_MEMORYPOOL_ON */

/// \}

} /* stLibErrCode */

#endif /* !__STLIB_ERRCODE_H__ */