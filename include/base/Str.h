
/// \brief Base class for strings.  Provides useful methods for strings.
#ifndef __STLIB_STRING_H__
#define __STLIB_STRING_H__

#include <vector>
#include "..\core\Def.h"
#include "..\Enum.h"

/// \defgroup base Stuff Base
/// \{

/// \brief Mmeory string operations
class stStrMem {

	friend class stStrW;
	friend class stStrA;

private:
	void				tryExtendMemW( wchar_t **ppsrc, const wchar_t *extra );
	void				tryExtendMemA( char **ppsrc, const char *extra );

public:
	wchar_t *		    NewAndCpyW( wchar_t **ppalloc, const wchar_t *cpySrc );
	wchar_t *			NewAndCpyW( const wchar_t *cpySrc );
	wchar_t *			NewW( wchar_t **ppalloc );
	wchar_t *			NewW();
	wchar_t *			ZeroMemW( wchar_t **ppsrc );
	wchar_t *			FitW( wchar_t **ppsrc );
	wchar_t *			AppendStrW( wchar_t **ppsrc, const wchar_t *appendSrc );
	wchar_t *			ExtendW( wchar_t **ppsrc, un32 newSize );
	void				SafeDelW( wchar_t **ppsrc );

	char *				NewAndCpyA( char **ppalloc, const char *cpySrc );
	char *				NewAndCpyA( const char *cpySrc );
	char *				NewA( char **ppalloc );
	char *				NewA();
	char *				ZeroMemA( char **ppsrc );
	char *				FitA( char **ppsrc );
	char *				AppendStrA( char **ppsrc, const char *appendSrc );
	char *				ExtendA( char **ppsrc, un32 newSize );
	void				SafeDelA( char **ppsrc );

	/// \brief Converts ASCI to Unicode. 
	/// \note  Unicode string pointer should be NULL, or it will be deleted,
	///		   as a result, this method maybe slow because of the memory allocation.
	wchar_t *			AToW( wchar_t **ppsrc, const char *targetSrc, const n32 codePage = 0 );
	
	/// \see   AToW
	char *				WToA( char **ppsrc, const wchar_t *targetSrc, const n32 codePage = 0 );

						stStrMem()  { }
	virtual				~stStrMem() { }
};

/// \brief Unicode string.
class stStrW {

    st_class_no_bin_cpy( stStrW )

protected:
	wchar_t	*		    m_pdata;
	bool				isWiderThanCurStr( const wchar_t *checkStr ) const;

	static stStrMem		m_mem;

public:
	bool				IsEqual( const wchar_t *compare )  const;
	bool			    IsEqual( const stStrW &compare )   const;
	bool				IsEmpty()						   const { return IsEqual( L"" ); }
	wchar_t * const		Data()						   	   const { return m_pdata; }
	wchar_t				At( const un32 index )	           const { return m_pdata[ index ]; }
	un32				Length()						   const { return wcslen( m_pdata ); }
	un32				RepTimesOf( const wchar_t key )    const;
	n32 				Find( const wchar_t key, const un32 times = 0 ) const;
	n32                 FindBack( const wchar_t key, const un32 times = 0 ) const;
	bool			    Split( const wchar_t key, std::vector<stStrW *> &words ) const;

	stStrW &			Clear();
	stStrW &			Append( const stStrW &text );
	stStrW &			Append( const wchar_t text );
	stStrW & 			Append( const wchar_t *text );
	stStrW &			Append( const wchar_t *text, const un32 len );
	stStrW &			SetStr( const wchar_t *text );
	stStrW &            SetStr( const stStrW &text );
	stStrW &		    Insert( un32 index, const wchar_t *text );
	stStrW &		    Delete( un32 headIndex, const un32 counts = 0 );
	stStrW &		    TrimFont(  const wchar_t key, const un32 times = 0 );
	stStrW &		    TrimBack(  const wchar_t key, const un32 times = 0 );
	stStrW &		    TrimSingle( stLibEnum::TRIMMODE flag );
	stStrW &		    Reverse();
	stStrW &		    Replace( const un32 headIndex, const wchar_t *text );

						stStrW();
						stStrW( const stStrW& cpy );
						stStrW( const wchar_t *cpy );
	virtual				~stStrW();
};

/// \brief ASCI string.
/// \see   stStrW
class stStrA {

    st_class_no_bin_cpy( stStrW )

protected:
	char *				m_pdata;
	bool				isWiderThanCurStr( const char *checkStr ) const;

	static stStrMem		m_mem;

public:
	bool				IsEqual( const char *compare )  const;
	bool			    IsEqual( const stStrA &compare )const;
	bool				IsEmpty()						const { return IsEqual( "" ); }
	char * const		Data()							const { return m_pdata; }
	char				At( const un32 index )	        const { return m_pdata[ index ]; }
	un32				Length()						const { return strlen( m_pdata ); }
	un32 				RepTimesOf( const char key )    const;
	n32				    Find( const char key, const un32 times = 0 ) const;
	n32                 FindBack( const char key, const un32 times = 0 ) const;
	bool			    Split( const char key, std::vector<stStrA *> &words ) const;

	stStrA &			Clear();
	stStrA &			Append( const stStrA &text );
	stStrA &			Append( const char text );
	stStrA & 			Append( const char *text );
	stStrA &			Append( const char *text, const un32 unLen );
	stStrA &			SetStr( const char *text );
	stStrA &		    Insert( un32 index, const char *text );
	stStrA &		    Delete( un32 headIndex, un32 counts = 0 );
	stStrA &		    TrimFont( const char key, const un32 times = 0 );
	stStrA &		    TrimBack( const char key, const un32 times = 0 );
	stStrA &		    TrimSingle( stLibEnum::TRIMMODE flag );
	stStrA &		    Reverse();
    stStrA &		    Replace( un32 headIndex, const char *text );

						stStrA();
                        stStrA( const stStrA &cpy );
						stStrA( const char *cpy );
	virtual				~stStrA();
};

/// \note should use const member only,  or a memory error will occur.
class stConstStrW : public stStrW {
private:
						stConstStrW();
public:
                        stConstStrW( wchar_t *kStr ) : stStrW( NULL ) { m_pdata = kStr; }
};

/// \see stConstStrW
class stConstStrA : public stStrA {
private:
						stConstStrA();
public:
                        stConstStrA( char *kStr ) : stStrA( NULL ) { m_pdata = kStr; }
};
/// \}

#endif /* !__STLIB_STRING_H__ */
