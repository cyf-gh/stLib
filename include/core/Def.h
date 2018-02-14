/**
 *	\breif �����˻�����stLib������ļ��������������е�stLib�ļ�֮ǰ
 */

#ifndef __STLIB_DEF_H__
#define __STLIB_DEF_H__

#include <cstdint>

/** \defgroup ��������
 *  stLib������Ļ�������
 *  \{
 */
typedef char			ch8;
typedef int8_t			n8;
typedef int16_t		    n16;
typedef int32_t		    n32, stResult;
typedef int64_t		    n64;
typedef uint8_t		    un8, byte8;
typedef uint16_t		un16;
typedef uint32_t		un32;
typedef uint64_t		un64;
typedef float			f32;
typedef double			f64;
/** \} */ 

/** \ingroup �궨��
 *  \{
 */

/** \brief		   ��ÿ���ڴ�ռ��ÿ�
 *	\param[in] p   �ڴ�ָ��
 *	\param[in] len �ڴ��С
 */
#define st_zero_memory( p, len ) \
	memset( p, 0, len )	

/** \brief		      �Ƿ�Ϊ����ķ���ֵ
 *	\param[in] result �������
 */
#define st_do_err( result )	\
	( ( ( stResult ) ( result ) ) < 0 )

/** \brief		   ��ȫ�ͷ�COM����
 *	\param[in out] COMָ��
 */
#define st_safe_rel( p ) \
if( p != NULL ) { \
	p->Release(); \
	p = NULL; \
}

/** \brief ǿ����ʹ���޷����ж����ƿ���
 *  \param class_name ����
 */
#define st_class_no_bin_cpy( class_name ) \
public: \
    class_name &operator=( const class_name& rhs ) = delete;

/** \} */ 

#define ST_NOERR				( ( stResult ) 0  )
#define ST_NOERR_INTERNAL		( ( stResult ) 10 )

/** \brief ��ʹ��stLib�Դ��꿪�ض��� */
#ifndef ST_DEF_DONOTUSESTLIBSWITCH
#include "..\Switch.h"
#endif /* !ST_DEF_DONOTUSESTLIBSWITCH */

#include "def\Platform.h"
#include "def\Build.h"

#ifdef __cplusplus

/** \brief �ͷŵ������ڴ�
 *  \see   st_new
 *		   st_new_class
 */
#	define st_safe_del( p ) \
if ( p != NULL ) { \
	delete p; \
	p = NULL; \
}

/** \brief �ͷ��������ڴ�
 *  \see   st_delete_class
 *		   st_delete
 */
#	define st_safe_del_arr( p ) \
if ( p != NULL ) { \
	delete [] p; \
	p = NULL; \
}

#	include "def\COMstd.h"

#endif /* !__cplusplus */

/** \} */ 

#endif /* !__STLIB_DEF_H__ */
