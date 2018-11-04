#pragma once

#include "stMemStr.hpp"
#include "_stdefs.h"

namespace_stLib {

/// \brief 字符串变化工具集
namespace String_Transform {
	/// \brief 从后往前剔除字符
	/// \param[typename] 字符串类型
	/// \param[in_out] ppdata 字符串类内部raw指针传入，无需关心
	/// \param[in] key 剔除至这个字符，该字符不剔除
	/// \param[in] times 至字符重复几次。0次为剔除至该字符第一次出现，以此类推
	/// \param[fill] st_arg_fill_3 占位宏
	template<typename type_of_char>
	void TrimFromBack( type_of_char** ppdata, const type_of_char key, const un times, st_arg_fill_3 ) {
		type_of_char	*pdata  = *ppdata;
		un				restTimes  = times;
		wchar_t			*curCh = &( pdata[ stLib_Mem::String::strLen( pdata ) - 1 ] );
		using namespace stLib_Mem::String;

		for ( ; curCh != pdata; --curCh ) {
			if ( *curCh == key ) {
				if ( restTimes == 0 ) {
					break;
				} else {
					--restTimes;
				}
			} else {
				*curCh = st_eos<type_of_char>();
			}
		}
	}
	/// \brief 反转字符串
	/// \param[typename] 字符串类型
	/// \param[in_out] ppdata 字符串类内部raw指针传入，无需关心
	/// \param[fill] st_arg_fill_5 占位宏
	template<typename type_of_char>
	void Reverse( type_of_char** ppdata, st_arg_fill_5 ) {
		for ( type_of_char *end = &( ( *ppdata )[ stLib_Mem::String::strLen( *ppdata ) - 1 ] ) , *head = ( *ppdata );
			end > head; --end, ++head ) {
			*end  ^= *head;
			*head ^= *end;
			*end  ^= *head;
		}
	}
	/// \brief 从前往后剔除字符
	/// \param[typename] 字符串类型
	/// \param[in_out] ppdata 字符串类内部raw指针传入，无需关心
	/// \param[in] key 剔除至这个字符，该字符不剔除
	/// \param[in] times 至字符重复几次。0次为剔除至该字符第一次出现，以此类推
	/// \param[fill] st_arg_fill_3 占位宏
	template<typename type_of_char>
	void TrimFromFont( type_of_char** ppdata, const type_of_char key, const un times, st_arg_fill_3 ) {
		Reverse<type_of_char>( ppdata, stLib_Mem::String::strLen<type_of_char>( *ppdata ), st_arg_fill_value_4 );
		TrimFromBack( ppdata, key, times, st_arg_fill_value_3 );
		Reverse<type_of_char>( ppdata, stLib_Mem::String::strLen<type_of_char>( *ppdata ), st_arg_fill_value_4 );
	}
	/// \brief 选择两边或者都是，并剔除单个字符
	/// \param[typename] 字符串类型
	/// \param[in_out] ppdata 字符串类内部raw指针传入，无需关心
	/// \param[in] ST_FrontOrBack 选择模式 \see stLib::ST_FrontOrBack
	template<typename type_of_char>
	void TrimSingle( type_of_char** ppdata, const ST_FrontOrBack flag, st_arg_fill_4 ) {
		type_of_char *pdata = *ppdata;
		using namespace stLib_Mem::String;
		
		if( 0 != stLib_Mem::String::strLen( pdata ) ) {
			switch ( flag ) {
			case ST_FrontOrBack::Back : {
				*( pdata + stLib_Mem::String::strLen( * ppdata ) - 1 ) = st_eos<type_of_char>();
				break;
			}
			case ST_FrontOrBack::Front : {
				Reverse<type_of_char>( ppdata, stLib_Mem::String::strLen( pdata ), st_arg_fill_value_4 );
				*( pdata + stLib_Mem::String::strLen( * ppdata ) - 1 ) = st_eos<type_of_char>();
				Reverse<type_of_char>( ppdata, stLib_Mem::String::strLen( pdata ), st_arg_fill_value_4 );
				break;
			}
			case ST_FrontOrBack::Both : {
				*( pdata + stLib_Mem::String::strLen( * ppdata ) - 1 ) = st_eos<type_of_char>();
				Reverse<type_of_char>( ppdata, stLib_Mem::String::strLen( pdata ), st_arg_fill_value_4 );
				*( pdata + stLib_Mem::String::strLen( * ppdata ) - 1 ) = st_eos<type_of_char>();
				Reverse<type_of_char>( ppdata, stLib_Mem::String::strLen( pdata ), st_arg_fill_value_4 );
				break;
			}
			}
		}
	}

} // String_Transform

namespace String_Utils {
	template<typename type_of_char>
	stStr_Dynamic<type_of_char> &st_TrimFrom( stStr_Dynamic<type_of_char> &ref_tstring, const type_of_char key, const un times, const ST_FrontOrBack from ) {
		switch ( from ) {
		case ST_FrontOrBack::Front :
			ref_tstring.Transform<const type_of_char, const un, st_arg_fill_3>( &(stLib::String_Transform::TrimFromFont), key, times, st_arg_fill_value_3 );
			break;
		case ST_FrontOrBack::Back :
			ref_tstring.Transform<const type_of_char, const un, st_arg_fill_3>( &(stLib::String_Transform::TrimFromBack), key, times, st_arg_fill_value_3 );
			break;
		case ST_FrontOrBack::Neither :
			// do nothing
			break;
		case ST_FrontOrBack::Both :
			ref_tstring.Transform<const type_of_char, const un, st_arg_fill_3>( &(stLib::String_Transform::TrimFromFont), key, times, st_arg_fill_value_3 );
			ref_tstring.Transform<const type_of_char, const un, st_arg_fill_3>( &(stLib::String_Transform::TrimFromBack), key, times, st_arg_fill_value_3 );
			break;
		}
		return ref_tstring;
	}

	template<typename type_of_char>
	stStr_Dynamic<type_of_char> &st_TrimSingle( stStr_Dynamic<type_of_char> &ref_tstring, const ST_FrontOrBack from ) {
		ref_tstring.Transform<const ST_FrontOrBack, st_arg_fill_4>( &(stLib::String_Transform::TrimSingle), from, st_arg_fill_value_4 );
		return ref_tstring;
	}

	template<typename type_of_char>
	stStr_Dynamic<type_of_char> &st_Reverse( stStr_Dynamic<type_of_char> &ref_tstring ) {
		ref_tstring.Transform<st_arg_fill_5>( &(stLib::String_Transform::Reverse), st_arg_fill_value_5 );
		return ref_tstring;
	}

	template<typename type_of_char> un32 GetRawMemSize( const stStr_Const<type_of_char> &ref );
	template<typename type_of_char>
	un32 GetRawMemSize( const stStr_Dynamic<type_of_char> &ref ) {
		return stLib_Mem::st_msize( ref.Raw() );
	}
}

} // stLib