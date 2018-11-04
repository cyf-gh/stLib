#pragma once

#include "stMemStr.hpp"

namespace_stLib {
//---------------------------------------------------------------------------
// Dynamic String
//---------------------------------------------------------------------------
template<typename type_of_char> class stStr_Dynamic {
public:
	using char_type = type_of_char;
	//---------------------------------------------------------------------------
	// Raw Refiners
	//---------------------------------------------------------------------------
	type_of_char At( const un index ) const { return m_pdata[ index ]; }
	const type_of_char *Raw() const { return m_pdata; }
	//---------------------------------------------------------------------------
	// Raw Infos
	//---------------------------------------------------------------------------
	n32	Find( const type_of_char key, 
			  const un rank,
			  const ST_FrontOrBack findFrom = ST_FrontOrBack::Front ) const;
	un RepTimesOf( const type_of_char key ) const;
	un Length() const;
	//---------------------------------------------------------------------------
	// Operations
	//---------------------------------------------------------------------------
	stStr_Dynamic<type_of_char> &Clear();
	stStr_Dynamic<type_of_char> &Delete( const un indexOfTheFirstChar, const un counts = 0 );
	stStr_Dynamic<type_of_char> &Append( const type_of_char text );
	stStr_Dynamic<type_of_char> &Append( const stStr_Dynamic<type_of_char> &text, const un length = 0 );
	stStr_Dynamic<type_of_char> &Append( const stStr_Const<const type_of_char> &text, const un length = 0 );
	stStr_Dynamic<type_of_char> &Append( const type_of_char *text, const un length = 0 );
	stStr_Dynamic<type_of_char> &Insert( const un index, const type_of_char *text );
	stStr_Dynamic<type_of_char> &Replace( const un indexOfTheFirstChar, const type_of_char *text );
	stStr_Dynamic<type_of_char> &SetStr( const type_of_char * text );
	stStr_Dynamic<type_of_char> &SetStr( const stStr_Dynamic<type_of_char> &text );
	stStr_Dynamic<type_of_char> &SetStr( const stStr_Const<const type_of_char> &text );
	template<typename T1, typename T2, typename T3, typename T4, typename T5>
	stStr_Dynamic<type_of_char> &Transform( 
		typename Traits_GenericFunctions<void, type_of_char**, T1, T2, T3, T4, T5, st_arg_fill>::type_p6Args func, 
		T1 a, T2 b, T3 c, T4 d, T5 e ) {
		(*func)( &m_pdata, a, b, c, d, e );
		return *this;
	}
	//---------------------------------------------------------------------------
	// Comparsions
	//---------------------------------------------------------------------------
	bool IsEqual( const type_of_char *compare ) const;
	bool IsEqual( const stStr_Dynamic<type_of_char> &compare ) const;
	bool IsEqual( const stStr_Const<const type_of_char> &compare ) const;
	//---------------------------------------------------------------------------
	// Conversations
	//---------------------------------------------------------------------------
	template<typename type_of_digit> stStr_Dynamic<type_of_char> &From( const type_of_digit t_dg ) {
		sprintf_( m_pdata, t_dg );
		return *this;
	}
	template<typename type_of_digit> type_of_digit ConvertTo() const {
		return stLib_Mem::String::StrToDigit<type_of_char, type_of_digit>( m_pdata );
	}
private:
	//---------------------------------------------------------------------------
	// Raw Data
	//---------------------------------------------------------------------------
	type_of_char *m_pstore;
	type_of_char *m_pdata;

public:
    stStr_Dynamic<type_of_char> &operator=( const stStr_Dynamic<type_of_char>& rhs ) = delete;
    stStr_Dynamic<type_of_char> &operator=( stStr_Dynamic<type_of_char>&& rhs ) = delete;

			 stStr_Dynamic();
    explicit stStr_Dynamic( const type_of_char* pstr );
	explicit stStr_Dynamic( const stStr_Dynamic<type_of_char> &rhs );
	explicit stStr_Dynamic( const stStr_Const<const type_of_char> &rhs );
	explicit stStr_Dynamic( stStr_Dynamic<type_of_char> &&rhs );
	virtual	 ~stStr_Dynamic();
};
//---------------------------------------------------------------------------
// Constant String
//---------------------------------------------------------------------------
template<typename type_of_char> class stStr_Const {
public:
	//---------------------------------------------------------------------------
	// Raw Refiners
	//---------------------------------------------------------------------------
	type_of_char At( const un index ) const { return m_pcdata[ index ]; }
	const type_of_char *Raw() const { return m_pcdata; }
	//---------------------------------------------------------------------------
	// Comparsions
	//---------------------------------------------------------------------------
	bool IsEqual( const type_of_char *compare ) const;
	bool IsEqual( const stStr_Dynamic<type_of_char> &compare ) const;
	bool IsEqual( const stStr_Const<type_of_char> &compare )	 const;
	//---------------------------------------------------------------------------
	// Raw Infos
	//---------------------------------------------------------------------------
	n32	Find( const type_of_char key, 
			  const un rank,
			  const ST_FrontOrBack flag = ST_FrontOrBack::Front ) const;
	un RepTimesOf( const type_of_char key ) const;
	un Length() const;

	template<typename type_of_digit> type_of_digit ConvertTo() const {
		return stLib_Mem::String::StrToDigit<type_of_char, type_of_digit>( m_pcdata );
	}
private:
	const type_of_char *m_pcdata;

public:
    stStr_Const<type_of_char> &operator=( const stStr_Const<type_of_char>& rhs ) = delete;
    stStr_Const<type_of_char> &operator=( stStr_Const<type_of_char>&& rhs )	= delete;
	stStr_Const() = delete;

    explicit stStr_Const( type_of_char* pstr ) { m_pcdata = pstr; }
	explicit stStr_Const( const stStr_Const<type_of_char> &rhs ) { m_pcdata = rhs.m_pcdata; }
	explicit stStr_Const( stStr_Const<type_of_char> &&rhs ) { m_pcdata = rhs.m_pcdata; }
	virtual	~stStr_Const() { }
};

} // stLib

