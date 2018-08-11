///
/// Created by caoyifan on 8/9/18.
///

#ifndef STLIB_STMEMSTR_H
#define STLIB_STMEMSTR_H

#include <stdlib.h>
#include <cwctype>
#include <string.h>
#include <stdio.h>
#include "stMem.h"
#include "stGeneralConcept.h"

namespace stLib_Mem {
	
namespace String {
	template<typename type_of_char>
	struct Traits_Char {
		static const un8 Traits_Char<type_of_char>::unSizeOfChar = sizeof( type_of_char );
		typedef typename type_of_char type_char;
	};
	static const un32 un_new_size_at_the_first_time = 64;
	//
	// Function Wrappers
	//
	// strLen
	template<typename Type> un32 strLen( const Type *p ) = delete;
	template<>ST_INLINE un32 strLen( const char *str )		{ return static_cast<un32>( strlen( str ) ); }
	template<>ST_INLINE un32 strLen( const wchar_t *str )	{ return static_cast<un32>( wcslen( str ) ); }
	// strLen
	// strCpy
	template<typename Type> void strCpy( typename Type **pp, const Type *cp) = delete;
	template<>ST_INLINE void strCpy( char **ppalloc, const char *cpySrc )		{ strcpy( *ppalloc, cpySrc ); }
	template<>ST_INLINE void strCpy( wchar_t **ppalloc, const wchar_t *cpySrc )	{ wcscpy( *ppalloc, cpySrc ); }
	// strCat
	template<typename Type> void strCat( typename Type **pp, const Type *cp) = delete;
	template<>ST_INLINE void strCat( char **ppalloc, const char *cpySrc )		{ strcat( *ppalloc, cpySrc ); }
	template<>ST_INLINE void strCat( wchar_t **ppalloc, const wchar_t *cpySrc )	{ wcscat( *ppalloc, cpySrc ); }
	// strCmp
	template<typename Type> bool strCmp( Type *p, Type *cp) = delete;
	template<>ST_INLINE bool strCmp( const char *p, const char *cp)				{ return strcmp( p, cp ); }
	template<>ST_INLINE bool strCmp( const wchar_t *p, const wchar_t *cp)		{ return wcscmp( p, cp ); }
	// sprintf
	template<typename Type, typename type_of_digit> type_of_digit sprintf_( Type *p, type_of_digit dg ) = delete;
	template<>ST_INLINE f64 sprintf_( char *p, const f64 fdg )		{ sprintf( p, "%lf", fdg ); return fdg; }
	template<>ST_INLINE n32 sprintf_( char *p, const n32 fdg )		{ sprintf( p, "%d", fdg );  return fdg; }
	template<>ST_INLINE f64 sprintf_( wchar_t *p, const f64 fdg )	{ swprintf( p, L"%lf", fdg ); return fdg; }
	template<>ST_INLINE n32 sprintf_( wchar_t *p, const n32 fdg )	{ swprintf( p, L"%d", fdg );  return fdg; }
	// Conversations
	template<typename Type, typename type_of_digit> type_of_digit StrToDigit( const Type *p ) = delete;
	template<>ST_INLINE n32 StrToDigit( const char *str ) { return atoi( str ); }
	template<>ST_INLINE n64 StrToDigit( const char *str ) { return atol( str ); }
	template<>ST_INLINE f64 StrToDigit( const char *str ) { return atof( str ); }
	template<>ST_INLINE n32 StrToDigit( const wchar_t *str ) { return _wtoi( str ); }
	template<>ST_INLINE n64 StrToDigit( const wchar_t *str ) { return _wtoi64( str ); }
	template<>ST_INLINE f64 StrToDigit( const wchar_t *str ) { return _wtof( str ); }
	
	template<typename type_of_char>
	n32 FindChar( const type_of_char *psrc, const type_of_char key, const un rank, const stLib::ST_FrontOrBack flag ) {
		un index = 0;
		un restRank = rank;

		if (flag == ST_FrontOrBack::Front) {
			const type_of_char *str = psrc;

			for (; *str != 0; ++str) {
				if (*str == key) {
					// assigned number position found
					if (restRank == 0) {
						return index;
					}
					else {
						--restRank;
					}
				}
				++index;
			}
		}
		else if (flag == ST_FrontOrBack::Back) {
			const type_of_char *str = &psrc[ strLen( static_cast<const type_of_char*>( psrc ) ) - 1];

			for (; str != psrc; --str) {
				if (*str == key) {
					// assigned number position found
					if (restRank == 0) {
						return index;
					}
					else {
						--restRank;
					}
				}
				++index;
			}
		}
		return -1;
	}

	template<typename type_of_char>
	un GetRepTimesOf( const type_of_char *psrc, type_of_char key ) {
		const type_of_char *str = psrc;
		un					times = 0;

		for( ; str != 0; ++str ) {
			times = ( *str == key ) ? times + 1 : times;
		}
		return times;
	}
	
	template<typename type_of_char>
	void SelfAppend( typename type_of_char **ppsrc ) {
		const un32 ognLen = strLen( *ppsrc );

		for ( un32 i = 0; i < ognLen; ++i) {
			*( *ppsrc + ognLen + i ) = *( *ppsrc + i );
		}
		*( *ppsrc + ( ognLen * 2 ) ) = NULL;
	}

	template<typename type_of_char>
	void TryExtendMem( typename type_of_char **ppsrc, const type_of_char *extra ) {
		const un32 curSize = st_msize( *ppsrc );

		if ( ( strLen( *ppsrc ) + strLen( extra ) ) >= ( curSize ) ) {
			Extend( ppsrc, curSize + strLen( extra ) + 1 );
		}
	}

	template<typename type_of_char>
	bool IsAWiderThanB( const type_of_char *pA, type_of_char *pB ) {
		return strLen( pA ) > st_msize( pB );
	}

	template<typename type_of_char>
    typename type_of_char * 
	NewAndCpy( typename type_of_char **ppalloc, const type_of_char *cpySrc ) {
		*ppalloc = st_new<type_of_char>( strLen( cpySrc ) + 1 );

		if ( nullptr == *ppalloc ) {
			return nullptr;
		}
		strCpy( ppalloc, cpySrc );
		return *ppalloc;
	}
	
	template<typename type_of_char>
    typename type_of_char *	
	NewAndCpy( const type_of_char *cpySrc ) {
	    type_of_char *src = nullptr;

		return NewAndCpy( &src, cpySrc );
	}

	template<typename type_of_char>
    typename type_of_char *	
	New( typename type_of_char **ppalloc ) {
		*ppalloc = st_new<type_of_char>( un_new_size_at_the_first_time );

		ZeroMem( ppalloc );
		return *ppalloc;
	}

	template<typename type_of_char>
    typename type_of_char *	
	New() {
		type_of_char *alloc = st_new<type_of_char>( un_new_size_at_the_first_time );

		if ( nullptr == alloc )
			return nullptr;
		ZeroMem( &alloc );
		return alloc;
	}

	template<typename type_of_char>
	typename type_of_char *	
	Fit( typename type_of_char **ppsrc )  {
		type_of_char *src = *ppsrc;

		*ppsrc = st_new<type_of_char>( strlen( *ppsrc ) + 1 );
		strCpy( *ppsrc, src );
		SafeDel( &src );
		return *ppsrc;
	}

	template<typename type_of_char>
    typename type_of_char *	
	AppendStr( typename type_of_char **ppsrc, const type_of_char *appendSrc ) {
		TryExtendMem( ppsrc, appendSrc );
		if ( *ppsrc == appendSrc ) {
			SelfAppend( ppsrc );
		} else {
			strCat( ppsrc, appendSrc );
		}
		return *ppsrc;
	}

 	template<typename type_of_char>
	typename type_of_char *	
	Extend( typename type_of_char **ppsrc, un32 newSize ) {
		type_of_char *src = *ppsrc;

		*ppsrc = st_new<type_of_char>( newSize );
		ZeroMem( ppsrc );
		strCpy( ppsrc, src );
		SafeDel( &src );
		return *ppsrc;
	}

  	template<typename type_of_char>
	typename type_of_char *	
	ZeroMem( typename type_of_char **ppsrc ) {
		st_zero_memory( *ppsrc, Traits_Char<type_of_char>::unSizeOfChar );
		return *ppsrc;
	}

	template<typename type_of_char>
    void SafeDel( typename type_of_char **ppsrc ) {
		st_delete_arr( ppsrc );
	}


#ifdef _ST_PLATFORM_WIN32
	ST_INLINE wchar_t *AToW( wchar_t **ppsrc, const char *targetSrc, const n32 codePage = 0 ) {
		const un newSize = MultiByteToWideChar( codePage, 0, targetSrc, -1, NULL, 0 );

		MultiByteToWideChar( codePage, 0, targetSrc, -1, *ppsrc, newSize );
		return *ppsrc;
	}
	ST_INLINE char *WToA( char **ppsrc, const wchar_t *targetSrc, const n32 codePage = 0 ) {
		const un newSize = WideCharToMultiByte( codePage, NULL, targetSrc, -1, NULL, 0, NULL, false );

		WideCharToMultiByte( codePage, NULL, targetSrc, -1, *ppsrc, newSize, NULL, false );
		return *ppsrc;
	}
#endif // _ST_PLATFORM_WIN32

} // stLib_Mem::String

} // stLib_Mem

#endif // STLIB_STMEMSTR_H
