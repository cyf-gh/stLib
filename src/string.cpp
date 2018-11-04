///
/// Created by caoyifan on 8/9/18.
///

#include "../include/stMemStr.hpp"
#include "../include/stString.h"

using namespace stLib;
using namespace stLib_Mem;
using namespace stLib_Mem::String;

//---------------------------------------------------------------------------
// stStr_Dynamic
//---------------------------------------------------------------------------
template<typename type_of_char>
bool stLib::stStr_Dynamic<type_of_char>::IsEqual( const type_of_char *compare ) const {
    return ! strCmp<const type_of_char>( compare, m_pdata );
}

template<typename type_of_char>
bool stLib::stStr_Dynamic<type_of_char>::IsEqual( const stStr_Dynamic<type_of_char>& compare ) const {
	return IsEqual( compare.Raw() );
}

template<typename type_of_char>
bool stLib::stStr_Dynamic<type_of_char>::IsEqual( const stStr_Const<const type_of_char>& compare ) const {
	return IsEqual( compare.Raw() );
}

template<typename type_of_char>
un stLib::stStr_Dynamic<type_of_char>::Length() const { return strLen<type_of_char>( m_pdata ); }


template<typename type_of_char>
un stLib::stStr_Dynamic<type_of_char>::RepTimesOf( const type_of_char key ) const {
	return GetRepTimesOf<const type_of_char>( m_pdata, key );
}

template<typename type_of_char>
n32 stStr_Dynamic<type_of_char>::Find( const type_of_char key, const un rank, const ST_FrontOrBack flag ) const {
	return FindChar<const type_of_char>( m_pdata, key, rank, flag );
}

template<typename type_of_char>
stStr_Dynamic<type_of_char>& stStr_Dynamic<type_of_char>::Clear() {
	ZeroMem( &m_pdata );
	return *this;
}
template<typename type_of_char>
stStr_Dynamic<type_of_char>& stStr_Dynamic<type_of_char>::Append( const type_of_char text ) {
	Append(&text);
	return *this;
}

template<typename type_of_char>
stStr_Dynamic<type_of_char>& stStr_Dynamic<type_of_char>::Append( const stStr_Dynamic<type_of_char>& text, const un length = 0 ) {
	Append( text.Raw(), length );
	return *this;
}

template<typename type_of_char>
stStr_Dynamic<type_of_char>& stLib::stStr_Dynamic<type_of_char>::Append( const stStr_Const<const type_of_char>& text, const un length = 0 ) {
	Append( text.Raw(), length );
	return *this;
}

template<typename type_of_char>
stStr_Dynamic<type_of_char>& stStr_Dynamic<type_of_char>::Append( const type_of_char * text, const un len = 0 ) {
	if ( len == 0 ) {
		AppendStr( &m_pdata, text );
	} else {
		const un orgLen = Length();

		AppendStr( &m_pdata, text );
		Delete( orgLen + len + 1 );
	}
	return *this;
}

template<typename type_of_char>
stStr_Dynamic<type_of_char>& stStr_Dynamic<type_of_char>::SetStr( const type_of_char *text ) {
	if ( nullptr == m_pdata ) {
		m_pdata = New<type_of_char>();
		ZeroMem( &m_pdata );
	} else if ( text == m_pdata ) { // Self Copy
		return *this;
	}

	if ( IsEqual( text ) ) {
		return *this;
	}
	if ( IsAWiderThanB( text, m_pdata ) ) {
		SafeDel( &m_pdata );
		NewAndCpy( &m_pdata, text );
	} else {
		strCpy( &m_pdata, text );
	}
	return *this;
}

template<typename type_of_char>
stStr_Dynamic<type_of_char>& stLib::stStr_Dynamic<type_of_char>::SetStr(const stStr_Dynamic<type_of_char> & text) {
    return SetStr( text.Raw() );
}

template<typename type_of_char>
stStr_Dynamic<type_of_char>& stLib::stStr_Dynamic<type_of_char>::SetStr(const stStr_Const<const type_of_char>& text) {
    return SetStr( text.Raw() );
}

template<typename type_of_char>
stStr_Dynamic<type_of_char>& stLib::stStr_Dynamic<type_of_char>::Insert( const un index, const type_of_char * text ) {
    static type_of_char	*store			 = st_allocator.NewArr<type_of_char>( strLen( text ) );
    type_of_char		*behindInsertPos = m_pdata + index;
	m_pstore							 = store;

    TryExtendMem( &m_pdata, text );

    ZeroMem( &store );
    TryExtendMem( &store, behindInsertPos ); // this must be safe
    AppendStr( &store, behindInsertPos );	 // store original string

    ZeroMem( &behindInsertPos );
    strCpy( &behindInsertPos, text );

    AppendStr( &m_pdata, store );
    return *this;
}

template<typename type_of_char>
stStr_Dynamic<type_of_char>& stLib::stStr_Dynamic<type_of_char>::Delete( const un indexOfFirstOne, const un counts ) {
    type_of_char *head = m_pdata + indexOfFirstOne;

    if ( counts == 0 || ( indexOfFirstOne + 1 + counts ) > strLen( head ) ) {
        *head = 0;
    } else {
        memmove( head, head + counts, strLen( head )  * Traits_Char<type_of_char>::unSizeOfChar );
    }
    return *this;
}

template<typename type_of_char>
stStr_Dynamic<type_of_char>& stLib::stStr_Dynamic<type_of_char>::Replace(const un indexOfTheFirstChar, const type_of_char * text) {
    type_of_char	*head = m_pdata + indexOfTheFirstChar;
    type_of_char	*end  = m_pdata + indexOfTheFirstChar + strLen( text );

    // ensure a eos is coped to the end of the string
    if ( Length() <= ( indexOfTheFirstChar + strLen( text ) ) ) {
        *end = st_eos<type_of_char>();
    }
    memmove( head, text, strLen( text ) * Traits_Char<type_of_char>::unSizeOfChar );
    return *this;
}

template<typename type_of_char>
stStr_Dynamic<type_of_char>::stStr_Dynamic() : m_pdata( nullptr ), m_pstore( nullptr ) {
	m_pdata = New<type_of_char>();
	ZeroMem( &m_pdata );
}

template<typename type_of_char>
stLib::stStr_Dynamic<type_of_char>::stStr_Dynamic( const type_of_char * pstr ) : m_pdata( nullptr ), m_pstore( nullptr ) {
    SetStr( pstr );
}

template<typename type_of_char>
stLib::stStr_Dynamic<type_of_char>::stStr_Dynamic(const stStr_Dynamic<type_of_char>& rhs) : m_pdata( nullptr ), m_pstore( nullptr ) {
    SetStr( rhs.Raw() );
}

template<typename type_of_char>
stLib::stStr_Dynamic<type_of_char>::stStr_Dynamic(const stStr_Const<const type_of_char>& rhs) : m_pdata( nullptr ), m_pstore( nullptr ) {
	SetStr( rhs );
}

template<typename type_of_char>
stLib::stStr_Dynamic<type_of_char>::stStr_Dynamic(stStr_Dynamic<type_of_char>&& rhs) : m_pdata( nullptr ), m_pstore( nullptr ) {
	if ( m_pdata != rhs.m_pdata ) { 
		m_pdata = rhs.m_pdata;
	}
	rhs.m_pdata = nullptr;
}

template<typename type_of_char>
stStr_Dynamic<type_of_char>::~stStr_Dynamic() {
	SafeDel( &m_pdata );
	SafeDel( &m_pstore );
}

//---------------------------------------------------------------------------
// stStr_Const
//---------------------------------------------------------------------------
template<typename type_of_char>
bool stLib::stStr_Const<type_of_char>::IsEqual( const type_of_char *compare ) const {
    return ! strCmp( compare, m_pcdata );
}

template<typename type_of_char>
bool stLib::stStr_Const<type_of_char>::IsEqual( const stStr_Dynamic<type_of_char>& compare ) const {
	return IsEqual( compare.Raw() );
}

template<typename type_of_char>
bool stLib::stStr_Const<type_of_char>::IsEqual( const stStr_Const<type_of_char>& compare ) const {
	return IsEqual( compare.Raw() );
}

template<typename type_of_char>
un stLib::stStr_Const<type_of_char>::Length() const { return strLen( m_pcdata ); }


template<typename type_of_char>
un stLib::stStr_Const<type_of_char>::RepTimesOf( const type_of_char key ) const {
	return GetRepTimesOf<type_of_char>( m_pcdata, key );
}

template<typename type_of_char>
n32 stStr_Const<type_of_char>::Find( const type_of_char key, const un rank, const ST_FrontOrBack flag ) const {
	return FindChar<type_of_char>( m_pcdata, key, rank, flag );
}

st_instance_template_class_in_cpp( stStr_Dynamic, char )
st_instance_template_class_in_cpp( stStr_Dynamic, wchar_t )
st_instance_template_class_in_cpp( stStr_Const, char )
st_instance_template_class_in_cpp( stStr_Const, wchar_t )