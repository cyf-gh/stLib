#include <gtest/gtest.h>
#include "..\include\stString.h"
#include "..\include\stStringExtra.h"
#include "..\include\stLib.h"
#pragma comment( lib, "gtestd.lib" )

TEST( stLib_Test, stString ) {
	stLib::stStrW str;
	stLib::stStrConstW c_str( L"123" );	

	EXPECT_TRUE( str.SetStr( L"123" ).IsEqual( L"123" ) );			// SetStr
	EXPECT_TRUE( str.Append( L"123" ).IsEqual( L"123123" ) );		// Append

	// L"123123"
	EXPECT_EQ( L'1', str.At( 0 ) );				// At
	EXPECT_STREQ( L"123123", str.Raw() );		// Raw

	EXPECT_EQ( 4, str.Find( L'2', 1 ) );											// Find From front
	EXPECT_EQ( 4, str.Find( L'2', 1, stLib::ST_FrontOrBack::Back ) );				// Find From back
	EXPECT_EQ( 2, str.RepTimesOf( L'2' ) );											// Repeat Times Of '2'
	EXPECT_EQ( 6, str.Length() );													// Length


	EXPECT_TRUE( str.Clear().IsEqual( L"" ) );				// Clear
	EXPECT_TRUE( str.SetStr( L"123123123123" ).Delete( 0 ).IsEqual( L"" ) );
	EXPECT_TRUE( str.SetStr( L"123123123123" ).Delete( 9, 6 ).IsEqual( L"123123123" ) );
	EXPECT_TRUE( str.SetStr( L"123123123123" ).Delete( 9, 2 ).IsEqual( L"123123123" ) );

	stLib::stStrW str2( std::move(str) );
	EXPECT_TRUE( str2.SetStr( c_str ).IsEqual( c_str ) );
	EXPECT_TRUE( str2.Append( c_str ).IsEqual( L"123123" ) );				
	EXPECT_TRUE( str2.Append( c_str.Raw() ).IsEqual( L"123123123" ) );
	EXPECT_TRUE( str2.SetStr( c_str ).IsEqual( c_str ) );
	EXPECT_TRUE( str2.Replace( 0, c_str.Raw() ).IsEqual( L"123" ) );


	EXPECT_TRUE( stLib::String_Utils::st_Reverse( str2 ).IsEqual( L"321" ) );
	EXPECT_TRUE( stLib::String_Utils::st_TrimSingle( str2, stLib::ST_FrontOrBack::Front ).IsEqual( L"21" ) );
	str2.SetStr( L"123123123" );
	EXPECT_TRUE( stLib::String_Utils::st_TrimFrom( str2, L'1', 1, stLib::ST_FrontOrBack::Front ).IsEqual( L"123123" ) );
}

TEST( stLib_Test, stStream ) {
	stLib::stStreamT a;
	stLib::stStreamHelperT b;
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	stLib::stStrW str( L"123123" );
	stLib::stStrW str2( L"123123" );

	stLib::stStrW str3( L"123123" );

	constexpr int i = 10;
	int arr[i];

	getchar();
	getchar();
    return 0;
}
