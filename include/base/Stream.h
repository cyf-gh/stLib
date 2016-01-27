/*

Base class for file stream and stream helper.  Provides file writing and reading methods.

*/

#ifndef __STLIB_STREAM_H__
#define __STLIB_STREAM_H__

class stStrW;

#include <stdio.h>
#include "..\core\Def.h"
#include "..\Enum.h"

/***********************************************************************

  Stream

***********************************************************************/

class stStream {

    st_class_no_bin_cpy( stStream )

protected:
	stLibEnum::FILEOPENMODE m_mode;		
	FILE *                  m_pfile;	
	un32					m_size;		
	bool					m_isOpen;	

public:
	void					Open( const stStrW &path, stLibEnum::FILEOPENMODE mode );
	void					Close();
	void					Move( const n32 pos, stLibEnum::FILEPOSITIONORG org );
	void					MoveHead();
    void                    SaveAs( const stStrW &newPath );
	void                    Save();
	un32					Size()		const { return m_size; }
	un32					Pos()		const { return ftell( m_pfile ); }
	bool					IsOpen()	const { return ( bool )m_isOpen; }
	bool					IsEOF()		const { return ( bool )feof( m_pfile ); }
	void *					Handle()	const { return m_pfile; }
	stLibEnum::FILEOPENMODE Mode()		const { return m_mode; }

							stStream();
	virtual					~stStream();
};

/***********************************************************************

  Stream helpers

***********************************************************************/

class stStreamHelper {

    st_class_no_bin_cpy( stStreamHelper )

protected:
	stStream				*m_pparent;

							stStreamHelper( const stStreamHelper & );

	FILE *					hfile()			  { return ( FILE * )m_pparent->Handle(); }
	stStream *				hstream()		  { return m_pparent; }

public:
	void					SetStream( stStream *parent )  { m_pparent = parent; }
	void					DeleteStream()			       { st_safe_del( m_pparent ); }
	stStream *				GetStream()				 const { return m_pparent; }

							stStreamHelper( stStream *pparent );
							stStreamHelper();
    virtual					~stStreamHelper();
};

class stStreamBinary : public stStreamHelper {
protected:
							stStreamBinary( const stStreamBinary & );

public:
	void					ReadBytes( const un32 counts, byte8 **ppdata );
	void					WriteBytes( const un32 counts, byte8 *data );

							stStreamBinary();
							stStreamBinary( stStream *pparent );
	virtual					~stStreamBinary();
};

class stStreamText : public stStreamHelper {
protected:
							stStreamText( const stStreamHelper & );

public:
	void					ReadText( const un32 counts, stStrW *ppstr );
	void					WriteText( const un32 counts, const stStrW &pstr );

							stStreamText( stStream *pparent );
							stStreamText();
	virtual					~stStreamText();
};

#endif /* !__STLIB_STREAM_H__ */
