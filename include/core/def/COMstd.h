#ifndef __STLIB_COMSTD_H__
#define __STLIB_COMSTD_H__

/** \defgroup COM�ӿڶ���
 *  �ӿڶ���
 *  \{
 */

/** \breif �����Զ�����Ϊ������ʽ��COM��ʽ */
#ifdef ST_SWITCH_BINCOM 
struct stIUNKNOWN {
	virtual HRESULT __stdcall QueryInterface( REFIID riid, void **ppvobject) = 0;
	virtual ULONG __stdcall AddRef(void) = 0;
	virtual ULONG __stdcall Release(void) = 0;	
};
#	define st_interface( interface_name )  struct interface_name : public stIUNKNOWN
#else
#	define st_interface( interface_name ) struct interface_name
#endif

#define st_interface_public_inherit( super_interface ) public super_interface
/** \} */ 

#endif /* !__STLIB_COMSTD_H__ */