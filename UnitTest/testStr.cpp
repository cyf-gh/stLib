#include <gtest/gtest.h>
#include "..\include\stString.h"

#pragma comment( lib, "gtestd.lib" )

TEST( stLib_Test, String_Member_Function_Test ) {
	stLib::stStrW str;

	EXPECT_EQ( true, str.SetStr( L"123" ).IsEqual(L"123") );
	EXPECT_EQ( true, str.Append( L"123" ).IsEqual(L"123123") );
	EXPECT_EQ( true, str.Append( str ).IsEqual(L"123123123123") );

	str.Transform<const wchar_t, const un, st_arg_fill_3>( &(stLib::String_Transform::TrimFromFont), L'1', 1, 0, 0, 0 );
	
	EXPECT_EQ( true, str.IsEqual( L"123123123" ) ); 
	
	EXPECT_EQ( 123123123, str.ConvertTo<n64>() );
	EXPECT_EQ( true, str.Clear().IsEqual(L"") );
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
	getchar();
    return 0;
}
