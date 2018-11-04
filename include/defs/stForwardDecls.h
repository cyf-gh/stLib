#pragma once

#define namespace_stLib		namespace stLib
#define namespace_stLib_Mem namespace stLib_Mem

namespace_stLib {
	//---------------------------------------------------------------------------
	// stString
	//---------------------------------------------------------------------------
	template<typename type_of_char> class stStr_Dynamic; 
	template<typename type_of_char> class stStr_Const;
	// FD
	template<typename type_of_char> class stStr_Dynamic; 
	template<typename type_of_char> class stStr_Const;

	using stStrW = stStr_Dynamic<wchar_t>;
	using stStrA = stStr_Dynamic<char>;
	using stStrConstW = stStr_Const<const wchar_t>;
	using stStrConstA = stStr_Const<const char>;
} // stLib