#include "..\include\base\Str.h"
#include "..\include\core\Core.h"

using namespace stLibEnum;

const un8 sizeofCH  = sizeof( char );
const un8 sizeofWCH = sizeof( wchar_t );

/*
==============================================================

    stStrMem

==============================================================
*/

/*
============
stStrMem::tryExtendMemW

Extends only when rest memory is not enough.
============
*/
void stStrMem::tryExtendMemW( wchar_t **ppsrc, const wchar_t *extra ) {
    const un32 curSize = ( st_sys_heap_memory_size( *ppsrc ) / sizeofWCH );

    if ( ( wcslen( *ppsrc ) + wcslen( extra ) ) >= ( curSize ) ) {
        ExtendW( ppsrc, curSize + wcslen( extra ) + 1 );
    }
}

/*
============
stStrMem::NewAndCpyW
============
*/
wchar_t *stStrMem::NewAndCpyW( wchar_t **ppalloc, const wchar_t *cpySrc ) {
    *ppalloc = st_new<wchar_t>( wcslen( *ppalloc ) + 1 );

    if ( NULL == *ppalloc ) {
        return NULL;
    }
    wcscpy( *ppalloc, cpySrc );
    return *ppalloc;
}

wchar_t *stStrMem::NewAndCpyW( const wchar_t *cpySrc ) {
    wchar_t *alloc = NULL;

    return NewAndCpyW( &alloc, cpySrc );
}

/*
============
stStrMem::NewW
============
*/
wchar_t *stStrMem::NewW( wchar_t **ppalloc ) {
    *ppalloc = st_new<wchar_t>( 50 );

    ZeroMemW( ppalloc );
    return *ppalloc;
}

wchar_t *stStrMem::NewW() {
    wchar_t *alloc = st_new<wchar_t>( 50 );

    if ( NULL == alloc )
        return NULL;
    ZeroMemW( &alloc );
    return alloc;
}

/*
============
stStrMem::SafeDelW
============
*/
void stStrMem::SafeDelW( wchar_t **ppsrc ) {
	st_delete_arr<wchar_t *>( ppsrc );
}

/*
============
stStrMem::ZeroMemW

Clears string content.
============
*/
wchar_t *stStrMem::ZeroMemW( wchar_t **ppsrc ) {
    st_zero_memory( *ppsrc, sizeofWCH );
    return *ppsrc;
}

/*
============
stStrMem::FitW

Eliminates extra heap space of string.
============
*/
wchar_t *stStrMem::FitW( wchar_t **ppsrc ) {
    wchar_t *src = *ppsrc;

    *ppsrc = st_new<wchar_t>( wcslen( *ppsrc ) + 1 );
    wcscpy( *ppsrc, src );
	SafeDelW( ppsrc );
	return *ppsrc;
}

/*
============
stStrMem::AppendStrW
============
*/
wchar_t *stStrMem::AppendStrW( wchar_t **ppsrc, const wchar_t *appendSrc ) {
    tryExtendMemW( ppsrc, appendSrc );
    wcscat( *ppsrc, appendSrc );
    return *ppsrc;
}

/*
============
stStrMem::ExtendW
============
*/
wchar_t *stStrMem::ExtendW( wchar_t **ppsrc, un32 newSize ) {
    wchar_t *src = *ppsrc;

    *ppsrc = st_new<wchar_t>( newSize );
    ZeroMemW( ppsrc );
    wcscpy( *ppsrc, src );
    SafeDelW( ppsrc );
    return *ppsrc;
}

/*
============
stStrMem::tryExtendMemA

Extends only when rest memory is not enough.
============
*/
void stStrMem::tryExtendMemA( char **ppsrc, const char *extra ) {
    const un32 curSize = st_sys_heap_memory_size( *ppsrc ) / sizeofWCH;

    if ( ( strlen( *ppsrc ) + strlen( extra ) ) >= ( curSize ) ) {
        ExtendA( ppsrc, curSize + strlen( extra ) + 1 );
    }
}

/*
============
stStrMem::NewAndCpyA
============
*/
char *stStrMem::NewAndCpyA( char **ppalloc, const char *cpySrc ) {
    *ppalloc = st_new<char>( strlen( cpySrc ) + 1 );

    if ( NULL == *ppalloc )
        return NULL;
    strcpy( *ppalloc, cpySrc );
    return *ppalloc;
}

char *stStrMem::NewAndCpyA( const char *cpySrc ) {
    char *src = NULL;

    return NewAndCpyA( &src, cpySrc );
}

/*
============
stStrMem::NewA
============
*/
char *stStrMem::NewA( char **ppalloc ) {
    *ppalloc = st_new<char>( 50 );

    ZeroMemA( ppalloc );
    return *ppalloc;
}

char *stStrMem::NewA() {
    char *alloc = st_new<char>( 50 );

    if ( NULL == alloc )
        return NULL;
    ZeroMemA( &alloc );
    return alloc;
}

/*
============
stStrMem::ZeroMemA

Clears string content.
============
*/
char *stStrMem::ZeroMemA( char **ppsrc ) {
    st_zero_memory( *ppsrc, sizeofCH );
    return *ppsrc;
}

/*
============
stStrMem::SafeDelA
============
*/
void stStrMem::SafeDelA( char **ppsrc ) { 
	st_delete_arr<char *>( ppsrc ); 
}

/*
============
stStrMem::FitA

Eliminates extra heap space of string.
============
*/
char *stStrMem::FitA( char **ppsrc ) {
    char *src = *ppsrc;

    *ppsrc = st_new<char>( strlen( *ppsrc ) + 1 );
    strcpy( *ppsrc, src );
    SafeDelA( &src );
    return *ppsrc;
}

char *stStrMem::AppendStrA( char **ppsrc, const char *appendSrc ) {
    tryExtendMemA( ppsrc, appendSrc );
    strcat( *ppsrc, appendSrc );
    return *ppsrc;
}

/*
============
stStrMem::ExtendA
============
*/
char *stStrMem::ExtendA( char **ppsrc, un32 newSize ) {
    char *src = *ppsrc;

    *ppsrc = st_new<char>( newSize );
    ZeroMemA( ppsrc );
    strcpy( *ppsrc, src );
    SafeDelA( &src );
    return *ppsrc;
}

/*
============
stStrMem::AToW

Converts ASCI to Unicode. Unicode string pointer should be NULL, or it will be deleted,
as a result, this method maybe slow because of the memory allocation.
============
*/
wchar_t *stStrMem::AToW( wchar_t **ppsrc, const char *targetSrc, const n32 codePage ) {
    const un32 newSize = MultiByteToWideChar( codePage, 0, targetSrc, -1, NULL, 0 );

    SafeDelW( ppsrc );		// prevent memory leak
    *ppsrc = st_new<wchar_t>( newSize );
    MultiByteToWideChar( codePage, 0, targetSrc, -1, *ppsrc, newSize );
    return *ppsrc;
}

/*
============
stStrMem::WToA

, which is similar to stLibUtils::string::AToW.
============
*/
char *stStrMem::WToA( char **ppsrc, const wchar_t *targetSrc, const n32 codePage ) {
    const un32 newSize = WideCharToMultiByte( codePage, NULL, targetSrc, -1, NULL, 0, NULL, false );

    SafeDelA( ppsrc ); // prevent memory leak
    *ppsrc = st_new<char>( newSize );
    WideCharToMultiByte( codePage, NULL, targetSrc, -1, *ppsrc, newSize, NULL, false );
    return *ppsrc;
}

/*
==============================================================

    stStrW

==============================================================
*/

/*
============
stStrW::isWiderThanCurStr
============
*/
bool stStrW::isWiderThanCurStr( const wchar_t *checkStr ) const {
    return wcslen( checkStr ) > ( st_sys_heap_memory_size( m_pdata ) / sizeofWCH );
}

/*
============
stStrW::m_mem
============
*/
stStrMem stStrW::m_mem = stStrMem();

/*
============
stStrW::stStrW
============
*/
stStrW::stStrW( void ) : m_pdata( NULL ) {
    m_pdata = m_mem.NewW();
    m_mem.ZeroMemW( &m_pdata );
}

stStrW::stStrW( const wchar_t *cpy ) : m_pdata( NULL ) {
    if ( cpy != NULL ) {
        SetStr( cpy );
    }
}

stStrW::stStrW( const stStrW& cpy ) : m_pdata( NULL ) {
    SetStr( cpy.Data() );
}

/*
============
stStrW::~stStrW
============
*/
stStrW::~stStrW() {
    st_delete_arr<wchar_t *>( &m_pdata );
}

/*
============
stStrW::Find

Returns times th's key's index.
============
*/
n32 stStrW::Find( const wchar_t key, const un32 times ) const {
    const wchar_t *str      = m_pdata;
    un32		  index     = 0;
    un32          restTimes = times;

    for( ; *str != 0; ++str ) {
        if( *str == key ) {
            // assigned number position found
            if ( restTimes == 0 ) {
                return index;
            } else {
                --restTimes;
            }
        }
        ++index;
    }
    return -1;
}

/*
============
stStrW::FindBack
============
*/
n32 stStrW::FindBack( const wchar_t key, const un32 times ) const {
    const wchar_t *str      = &m_pdata[ Length() -1 ];
    un32		  index     = 0;
    un32          restTimes = times;

    for( ; str != m_pdata; --str ) {
        if( *str == key ) {
            // assigned number position found
            if ( restTimes == 0 ) {
                return index;
            } else {
                --restTimes;
            }
        }
        ++index;
    }
    return -1;
}

/*
============
stStrW::RepTimesOf
============
*/
un32 stStrW::RepTimesOf( const wchar_t key ) const {
	const wchar_t *str  = m_pdata;
	un32		  times = 0;

	for( ; str != 0; ++str ) {
		times = ( *str == key ) ? times + 1 : times;
	}
	return times;
}

/*
============
stStrW::IsEqual
============
*/
bool stStrW::IsEqual( const wchar_t *compare ) const {
    return ! wcscmp( m_pdata, compare );
}

bool stStrW::IsEqual( const stStrW &compare ) const {
    return IsEqual( compare.Data() );
}

/*
============
stStrW::Clear
============
*/
stStrW &stStrW::Clear() {
    m_mem.ZeroMemW( &m_pdata );
    return *this;
}

/*
============
stStrW::Append
============
*/
stStrW &stStrW::Append( const wchar_t *text ) {
    m_mem.AppendStrW( &m_pdata, text );
    return *this;
}

stStrW &stStrW::Append( const wchar_t text ) {
    Append( &text );
    return *this;
}

stStrW &stStrW::Append( const stStrW &text ) {
    Append( text.Data() );
    return *this;
}

stStrW &stStrW::Append( const wchar_t *text, const un32 len ) {
    const un32 orgLen = Length();

    Append( text );
    m_pdata[ orgLen + len + 1 ] = L'\0';
    return *this;
}

/*
============
stStrW::SetStr
============
*/
stStrW &stStrW::SetStr( const wchar_t *text ) {
    if ( NULL == m_pdata ) {
        m_pdata = m_mem.NewW();
        m_mem.ZeroMemW( &m_pdata );
    }
    if ( isWiderThanCurStr( text ) ) {
        m_mem.SafeDelW( &m_pdata );
        m_mem.NewAndCpyW( &m_pdata, text );
    } else {
        wcscpy( m_pdata, text );
    }
    return *this;
}

/*
============
stStrW::SetStr
============
*/
stStrW &stStrW::SetStr( const stStrW &text ) {
    return SetStr( text.Data() );
}

/*
============
stStrW::TrimBack
============
*/
stStrW &stStrW::TrimBack( const wchar_t key, const un32 times ) {
    un32	    restTimes  = times;
    wchar_t		*curCh = &( m_pdata[ Length() - 1 ] );

    for ( ; curCh != m_pdata; --curCh ) {
        if ( *curCh == key ) {
            if ( restTimes == 0 ) {
                break;
            } else {
                --restTimes;
            }
        } else {
            *curCh = L'\0';
        }
    }
    return *this;
}

/*
============
stStrW::TrimFont
============
*/
stStrW &stStrW::TrimFont( const wchar_t key, const un32 times ) {
    Reverse();
    TrimBack( key, times );
    Reverse();
    return *this;
}

/*
============
stStrW::TrimSingle
============
*/
stStrW &stStrW::TrimSingle( stLibEnum::TRIMMODE flag ) {
    const un32    len = Length();

	if( 0 != len ) {
		switch ( flag ) {
		case TM_RIGHT : {
			*( m_pdata + len - 1 ) = L'\0';
			break;
		}
		case TM_LEFT : {
			Reverse();
			*( m_pdata + len - 1 ) = L'\0';
			Reverse();
			break;
		}
		case TM_BOTH_SIDE : {
			*( m_pdata + len - 1 ) = L'\0';
			Reverse();
			*( m_pdata + len - 1 ) = L'\0';
			Reverse();
			break;
		}
		}
	}
    return *this;
}

/*
============
stStrW::Reverse
============
*/
stStrW &stStrW::Reverse() {
    for ( wchar_t *end = &( m_pdata[ Length() - 1 ] ) , *head = ( m_pdata );
        end > head; --end, ++head ) {
        *end  ^= *head;
        *head ^= *end;
        *end  ^= *head;
    }
    return *this;
}

/*
============
stStrW::Split
============
*/
bool stStrW::Split( const wchar_t key, std::vector<stStrW *> &words ) const {
    const wchar_t   *str = m_pdata;
    stStrW			word;

    for ( un32 i = 0; i < ( Length() + 1 ); ++i ) {
        if ( *str == key ) {
            words.push_back( st_new_class<stStrW>( stStrW( word.Data() ) ) );
        } else {
            word.Append( &( *str ) );
            ++str;
        }
    }
    return words.size();
}

/*
============
stStrW::Insert
============
*/
stStrW &stStrW::Insert( un32 index, const wchar_t *text ) {
    static wchar_t *store			 = st_new<wchar_t>( wcslen( text ) );
    wchar_t		   *behindInsertPos  = m_pdata + index;

    m_mem.tryExtendMemW( &m_pdata, text );

    m_mem.ZeroMemW( &store );
    m_mem.tryExtendMemW( &store, behindInsertPos ); // this must be safe
    m_mem.AppendStrW( &store, behindInsertPos );	 // store original string

    m_mem.ZeroMemW( &behindInsertPos );
    wcscpy( behindInsertPos, text );

    m_mem.AppendStrW( &m_pdata, store );
    return *this;
}

/*
============
stStrW::Replace
============
*/
stStrW &stStrW::Replace( un32 headIndex, const wchar_t *text ) {
    wchar_t		   *head = m_pdata + headIndex;
    wchar_t		   *end  = m_pdata + headIndex + wcslen( text );

    // ensure a '\0' is coped to the end of the string
    if ( Length() <= ( headIndex + wcslen( text ) ) ) {
        *end = L'\0';
    }
    memmove( head, text, wcslen( text ) * sizeofWCH );
    return *this;
}

/*
============
stStrW::Delete
============
*/
stStrW &stStrW::Delete( un32 headIndex, un32 counts ) {
    wchar_t         *head = m_pdata + headIndex;

    if ( counts == 0 ) {
        *head = NULL;
    } else {
        memmove( head, head + counts, wcslen( head )  * sizeofWCH );
    }
    return *this;
}

/*
==============================================================

    stStrA

==============================================================
*/

/*
============
stStrA::isWiderThanCurStr
============
*/
bool stStrA::isWiderThanCurStr( const char *checkStr ) const {
    return strlen( checkStr ) > ( st_sys_heap_memory_size( m_pdata ) / sizeofCH );
}

/*
============
stStrA::m_mem
============
*/
stStrMem stStrA::m_mem = stStrMem();

/*
============
stStrA::stStrA
============
*/
stStrA::stStrA( void ) : m_pdata( NULL ) {
    m_pdata = m_mem.NewA();
    m_mem.ZeroMemA( &m_pdata );
}

stStrA::stStrA( const char *cpy ) : m_pdata( NULL ) {
    SetStr( cpy );
}

stStrA::stStrA( const stStrA &cpy ) : m_pdata( NULL ) {
    SetStr( cpy.Data() );
}

/*
============
stStrA::~stStrA
============
*/
stStrA::~stStrA() {
    m_mem.SafeDelA( &m_pdata );
}

/*
============
stStrA::Find
============
*/
n32 stStrA::Find( const char key, const un32 times ) const {
    const char	  *str      = m_pdata;
    un32		  index     = 0;
    un32          restTimes = times;

    for( ; *str != 0; ++str ) {
        if( *str == key ) {
            // assigned number position found
            if ( restTimes == 0 ) {
                return index;
            } else {
                --restTimes;
            }
        }
        ++index;
    }
    return -1;
}

/*
============
stStrA::FindBack
============
*/
n32 stStrA::FindBack( const char key, const un32 times ) const {
    const char	  *str      = &m_pdata[ Length() - 1 ];
    un32		  index     = 0;
    un32          restTimes = times;

    for( ; str != m_pdata; --str ) {
        if( *str == key ) {
            // assigned number position found
            if ( restTimes == 0 ) {
                return index;
            } else {
                --restTimes;
            }
        }
        ++index;
    }
    return -1;
}

/*
============
stStrA::RepTimesOf
============
*/
un32 stStrA::RepTimesOf( const char key ) const {
	const char    *str  = m_pdata;
	un32		  times = 0;

	for( ; str != 0; ++str ) {
		times = ( *str == key ) ? times + 1 : times;
	}
	return times;
}

/*
============
stStrA::IsEqual
============
*/
bool stStrA::IsEqual( const char *compare ) const {
    return ! strcmp( m_pdata, compare );
}

bool stStrA::IsEqual( const stStrA &compare ) const {
    return IsEqual( compare.Data() );
}

/*
============
stStrA::Clear
============
*/
stStrA &stStrA::Clear() {
    m_mem.ZeroMemA( &m_pdata );
    return *this;
}

/*
============
stStrA::Append
============
*/
stStrA &stStrA::Append( const char *text ) {
    m_mem.AppendStrA( &m_pdata, text );
    return *this;
}

stStrA &stStrA::Append( const stStrA &text ) {
    Append( text.Data() );
    return *this;
}

stStrA &stStrA::Append( const char chText ) {
    Append( &chText );
    return *this;
}

stStrA &stStrA::Append( const char *text, const un32 len ) {
    const un32 orgLen = Length();

    Append( text );
    m_pdata[ orgLen + len + 1 ] = L'\0';
    return *this;
}

/*
============
stStrA::SetStr
============
*/
stStrA &stStrA::SetStr( const char *text ) {
    if ( NULL == m_pdata ) {
        m_pdata = m_mem.NewA();
        m_mem.ZeroMemA( &m_pdata );
    }
    if ( isWiderThanCurStr( text ) ) {
        m_mem.SafeDelA( &m_pdata );
        m_mem.NewAndCpyA( &m_pdata, text );
    } else {
        strcpy( m_pdata, text );
    }
    return *this;
}

/*
============
stStrA::TrimFont
============
*/
stStrA &stStrA::TrimFont( const char key, const un32 times ) {
    un32	    index  = times;
    char		*curCh = &( m_pdata[ Length() - 1 ] );

    for ( ; curCh != m_pdata; --curCh ) {
        if ( *curCh == key ) {
            if ( index == 0 ) {
                break;
            } else {
                --index;
            }
        } else {
            *curCh = L'\0';
        }
    }
    return *this;
}

/*
============
stStrA::TrimBack
============
*/
stStrA &stStrA::TrimBack( const char key, const un32 times ) {
    Reverse();
    TrimFont( key, times );
    Reverse();
    return *this;
}

/*
============
stStrA::TrimSingle
============
*/
stStrA &stStrA::TrimSingle( stLibEnum::TRIMMODE flag ) {
    const un32    len  = Length();

    switch ( flag ) {
    case TM_RIGHT : {
        *( m_pdata + len - 1 ) = L'\0';
        break;
    }
    case TM_LEFT : {
        Reverse();
        *( m_pdata + len - 1 ) = L'\0';
        Reverse();
        break;
    }
    case TM_BOTH_SIDE : {
        *( m_pdata + len - 1 ) = L'\0';
        Reverse();
        *( m_pdata + len - 1 ) = L'\0';
        Reverse();
        break;
    }
    }
    return *this;
}

/*
============
stStrA::Reverse
============
*/
stStrA &stStrA::Reverse() {
    for ( char *end = &( m_pdata[ Length() - 1 ] ) , *head = m_pdata;
        end > head; --end, ++head ) {
        *end  ^= *head;
        *head ^= *end;
        *end  ^= *head;
    }
    return *this;
}

/*
============
stStrA::Split
============
*/
bool stStrA::Split( const char key, std::vector<stStrA *> &words ) const {
    const char   *str = m_pdata;
    stStrA		 word;

    for ( un32 i = 0; i < ( Length() + 1 ); ++i ) {
        if ( *str == key ) {
            words.push_back( st_new_class<stStrA>( stStrA( word.Data() ) ) );
        } else {
            word.Append( &( *str ) );
            ++str;
        }
    }
    return words.size();
}

/*
============
stStrA::Insert
============
*/
stStrA &stStrA::Insert( un32 index, const char *text ) {
    static char    *store            = st_new<char>( strlen( text ) );
    char		   *behindInsertPos  = m_pdata + index;

    m_mem.tryExtendMemA( &m_pdata, text );

    m_mem.ZeroMemA( &store );
    m_mem.tryExtendMemA( &store, behindInsertPos ); // this must be safe
    m_mem.AppendStrA( &store, behindInsertPos );    // store original string

    m_mem.ZeroMemA( &behindInsertPos );
    strcpy( behindInsertPos, text );

    m_mem.AppendStrA( &m_pdata, store );
    return *this;
}

/*
============
stStrA::Replace
============
*/
stStrA &stStrA::Replace( un32 headIndex, const char *text ) {
    char		   *head = m_pdata + headIndex;
    char		   *end  = m_pdata + headIndex + strlen( text );

    // ensure a '\0' is coped to the end of the string
    if ( Length() <= ( headIndex + strlen( text ) ) ) {
        *end = L'\0';
    }
    memmove( head, text, strlen( text ) * sizeofCH );
    return *this;
}

/*
============
stStrA::Delete
============
*/
stStrA &stStrA::Delete( un32 headIndex, un32 counts ) {
    char           *head = m_pdata + headIndex;

    if ( counts == 0 ) {
        *head = '\0';
    } else {
        memmove( head, head + counts, strlen( head )  * sizeofCH );
    }
    return *this;
}
