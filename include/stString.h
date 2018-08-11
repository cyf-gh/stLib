///
/// Created by caoyifan on 8/9/18.
///
#pragma once

#include "stDef.h"
#include "stMemStr.hpp"
#include "stGeneralConcept.h"
#include "stGenericSupport.h"

namespace stLib {

// FD
template<typename type_of_char> class stStr_Dynamic; 
template<typename type_of_char> class stStr_Const;

using stStrW = stStr_Dynamic<wchar_t>;
using stStrA = stStr_Dynamic<char>;
using stStrConstW = stStr_Const<const wchar_t>;
using stStrConstA = stStr_Const<const char>;

//---------------------------------------------------------------------------
// Dynamic String
//---------------------------------------------------------------------------
template<typename type_of_char> class stStr_Dynamic {
public:
	//---------------------------------------------------------------------------
	// Raw Refiners
	//---------------------------------------------------------------------------
	type_of_char		At( const un index )								const { return m_pdata[ index ]; }
	const type_of_char *Raw()												const { return m_pdata; }
	//---------------------------------------------------------------------------
	// Raw Infos
	//---------------------------------------------------------------------------
	n32					Find( const type_of_char key, 
							  const un rank,
							  const ST_FrontOrBack flag = ST_FrontOrBack::Front ) 
																			const;
	un					RepTimesOf( const type_of_char key )				const;
	un					Length()											const;
	//---------------------------------------------------------------------------
	// Operations
	//---------------------------------------------------------------------------
	stStr_Dynamic<type_of_char> &Clear();
	stStr_Dynamic<type_of_char> &Delete( un indexOfTheFirstChar, const un counts = 0 );
	stStr_Dynamic<type_of_char> &Append( const type_of_char text );
	stStr_Dynamic<type_of_char> &Append( const stStr_Dynamic<type_of_char> &text, const un length = 0 );
	stStr_Dynamic<type_of_char> &Append( const stStr_Const<type_of_char> &text, const un length = 0 );
	stStr_Dynamic<type_of_char> &Append( const type_of_char *text, const un length = 0 );
	stStr_Dynamic<type_of_char> &Insert( un index, const type_of_char *text );
	stStr_Dynamic<type_of_char> &Replace( const un indexOfTheFirstChar, const type_of_char *text );
	stStr_Dynamic<type_of_char> &SetStr( const type_of_char * text );
	stStr_Dynamic<type_of_char> &SetStr( const stStr_Dynamic<type_of_char> &text );
	stStr_Dynamic<type_of_char> &SetStr( const stStr_Const<type_of_char> &text );
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
	bool				IsEqual( const type_of_char *compare )					const;
	bool			    IsEqual( const stStr_Dynamic<type_of_char> &compare )	const;
	bool			    IsEqual( const stStr_Const<type_of_char> &compare )		const;
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
	type_of_char								*m_pstore;
	type_of_char								*m_pdata;

public:
    stStr_Dynamic<type_of_char> &operator=( const stStr_Dynamic<type_of_char>& rhs )	= delete;
    stStr_Dynamic<type_of_char> &operator=( stStr_Dynamic<type_of_char>&& rhs )			= delete;

						stStr_Dynamic();
    explicit			stStr_Dynamic( const type_of_char* pstr );
	explicit			stStr_Dynamic( const stStr_Dynamic<type_of_char> &rhs );
	explicit			stStr_Dynamic( const stStr_Const<type_of_char> &rhs );
	explicit			stStr_Dynamic( stStr_Dynamic<type_of_char> &&rhs );
	virtual				~stStr_Dynamic();
};

template<typename type_of_char> class stStr_Const {
public:
	//---------------------------------------------------------------------------
	// Raw Refiners
	//---------------------------------------------------------------------------
	type_of_char		At( const un index )								const { return m_pcdata[ index ]; }
	const type_of_char *Raw()												const { return m_pcdata; }
	//---------------------------------------------------------------------------
	// Comparsions
	//---------------------------------------------------------------------------
	bool				IsEqual( const type_of_char *compare )					const;
	bool			    IsEqual( const stStr_Dynamic<type_of_char> &compare )	const;
	bool			    IsEqual( const stStr_Const<type_of_char> &compare )		const;
	//---------------------------------------------------------------------------
	// Raw Infos
	//---------------------------------------------------------------------------
	n32					Find( const type_of_char key, 
							  const un rank,
							  const ST_FrontOrBack flag = ST_FrontOrBack::Front ) 
																			const;
	un					RepTimesOf( const type_of_char key )						const;
	un					Length()											const;

	template<typename type_of_digit> type_of_digit ConvertTo() const {
		return stLib_Mem::String::StrToDigit<type_of_char, type_of_digit>( m_pcdata );
	}
private:
	const type_of_char *m_pcdata;

public:
    stStr_Const<type_of_char> &operator=( const stStr_Const<type_of_char>& rhs )	= delete;
    stStr_Const<type_of_char> &operator=( stStr_Const<type_of_char>&& rhs )			= delete;
	stStr_Const()																	= delete;

    explicit			stStr_Const( type_of_char* pstr ) { m_pcdata = pstr; }
	explicit			stStr_Const( const stStr_Const<type_of_char> &rhs ) { m_pcdata = rhs.m_pcdata; }
	explicit			stStr_Const( stStr_Const<type_of_char> &&rhs ) { m_pcdata = rhs.m_pcdata; }
	virtual				~stStr_Const() { }
};

/// \brief �ַ����仯���߼�
namespace String_Transform {
	/// \brief �Ӻ���ǰ�޳��ַ�
	/// \param[typename] �ַ�������
	/// \param[in_out] ppdata �ַ������ڲ�rawָ�봫�룬�������
	/// \param[in] key �޳�������ַ������ַ����޳�
	/// \param[in] times ���ַ��ظ����Ρ�0��Ϊ�޳������ַ���һ�γ��֣��Դ�����
	/// \param[fill] st_arg_fill_3 ռλ��
	template<typename type_of_char>
	void TrimFromBack( type_of_char** ppdata, const type_of_char key, const un times, st_arg_fill_3 ) {
		type_of_char	*pdata  = *ppdata;
		un				restTimes  = times;
		wchar_t			*curCh = &( pdata[ stLib_Mem::String::strLen( pdata ) - 1 ] );

		for ( ; curCh != pdata; --curCh ) {
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
	}
	/// \brief ��ת�ַ���
	/// \param[typename] �ַ�������
	/// \param[in_out] ppdata �ַ������ڲ�rawָ�봫�룬�������
	/// \param[fill] st_arg_fill_5 ռλ��
	template<typename type_of_char>
	void Reverse( type_of_char** ppdata, st_arg_fill_5 ) {
		for ( type_of_char *end = &( ( *ppdata )[ stLib_Mem::String::strLen( *ppdata ) - 1 ] ) , *head = ( *ppdata );
			end > head; --end, ++head ) {
			*end  ^= *head;
			*head ^= *end;
			*end  ^= *head;
		}
	}
	/// \brief ��ǰ�����޳��ַ�
	/// \param[typename] �ַ�������
	/// \param[in_out] ppdata �ַ������ڲ�rawָ�봫�룬�������
	/// \param[in] key �޳�������ַ������ַ����޳�
	/// \param[in] times ���ַ��ظ����Ρ�0��Ϊ�޳������ַ���һ�γ��֣��Դ�����
	/// \param[fill] st_arg_fill_3 ռλ��
	template<typename type_of_char>
	void TrimFromFont( type_of_char** ppdata, const type_of_char key, const un times, st_arg_fill_3 ) {
		Reverse<type_of_char>( ppdata, stLib_Mem::String::strLen<type_of_char>( *ppdata ), st_arg_fill_value_4 );
		TrimFromBack( ppdata, key, times, st_arg_fill_value_3 );
		Reverse<type_of_char>( ppdata, stLib_Mem::String::strLen<type_of_char>( *ppdata ), st_arg_fill_value_4 );
	}
	/// \brief ѡ�����߻��߶��ǣ����޳������ַ�
	/// \param[typename] �ַ�������
	/// \param[in_out] ppdata �ַ������ڲ�rawָ�봫�룬�������
	/// \param[in] ST_FrontOrBack ѡ��ģʽ \see stLib::ST_FrontOrBack
	template<typename type_of_char>
	void TrimSingle( type_of_char** ppdata, const ST_FrontOrBack flag, st_arg_fill_4 ) {
		type_of_char *pdata = *ppdata;

		if( 0 != stLib_Mem::String::strLen( pdata ) ) {
			switch ( flag ) {
			case ST_FrontOrBack::Back : {
				*( pdata + len - 1 ) = L'\0';
				break;
			}
			case ST_FrontOrBack::Front : {
				Reverse<type_of_char>( ppdata, stLib_Mem::String::strLen( pdata ), st_arg_fill_value_4 );
				*( pdata + len - 1 ) = L'\0';
				Reverse<type_of_char>( ppdata, stLib_Mem::String::strLen( pdata ), st_arg_fill_value_4 );
				break;
			}
			case ST_FrontOrBack::Both : {
				*( pdata + len - 1 ) = L'\0';
				Reverse<type_of_char>( ppdata, stLib_Mem::String::strLen( pdata ), st_arg_fill_value_4 );
				*( pdata + len - 1 ) = L'\0';
				Reverse<type_of_char>( ppdata, stLib_Mem::String::strLen( pdata ), st_arg_fill_value_4 );
				break;
			}
			}
		}
	}

} // stLib_String_Transform

} // stLib

