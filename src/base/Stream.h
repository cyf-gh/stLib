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
	stLibEnum::FILEOPENMODE m_mode;		// file opening mode
	FILE *                  m_pfile;	// file handle
	un32					m_size;		// bit unit size
	bool					m_isOpen;	// if there has been a file handle

public:
	void					Open( const wchar_t *path, stLibEnum::FILEOPENMODE mode );
	void					Close();
	void					Flush();
	void					Move( const n32 pos, stLibEnum::FILEPOSITIONORG org );
	void					MoveHead();
    void                    Save( const wchar_t *newPath );
	un32					GetSize()		const { return m_size; }
	un32					GetPos()		const { return ftell( m_pfile ); }
	bool					IsOpen()		const { return ( bool )m_isOpen; }
	bool					IsEOF()			const { return ( bool )feof( m_pfile ); }
	void *					GetHandle()		const { return m_pfile; }
	stLibEnum::FILEOPENMODE GetMode()		const { return m_mode; }

							stStream();
	virtual					~stStream();
};

/***********************************************************************

  Stream helpers

***********************************************************************/

class stStreamHelper {

    st_class_no_bin_cpy( stStreamHelper )

protected:
	stStream				*m_pParent;

							stStreamHelper( const stStreamHelper & );

	FILE *					hfile()				{ return ( FILE * )m_pParent->GetHandle(); }
	stStream *				hstream()			{ return m_pParent ; }

public:
	void					SetStream( stStream *parent )  { m_pParent = parent; }
	void					DeleteStream()			       { st_safe_del( m_pParent ); }
	stStream *				GetStream()				 const { return m_pParent; }

							stStreamHelper( stStream *parent );
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
							stStreamBinary( stStream *parent );
	virtual					~stStreamBinary();
};

class stStreamText : public stStreamHelper {
protected:
							stStreamText( const stStreamHelper & );

public:
	void					ReadText( const un32 counts, stStrW *ppstr );
	void					WriteText( const un32 counts, const stStrW &pstr );

							stStreamText( stStream *parent );
							stStreamText();
	virtual					~stStreamText();
};

#endif /* !__STLIB_STREAM_H__ */
