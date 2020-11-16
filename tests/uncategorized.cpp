#include <iostream>
#include <string>
#include <unistd.h>
#include <memory>

#include "gtest/gtest.h"

#include "b.h"
#include "bobj.h"
#include "bint.h"
#include "i2par.h"
// #include "i1nur.h"   // bint1/

extern "C"
{
	Visible char *OPTbwsdir= (char *) NULL;
	Visible char *OPTworkspace= (char *) NULL;
	Visible char *OPTcentral= (char *) NULL;
	Visible char *OPTeditor= (char *) NULL;
	Visible bool OPTunpack= No;
	Visible bool OPTslowterminal= No;
	Visible int abc_todo = 1;
}

std::shared_ptr<char[]> mk_string(const char* s)
{
	const size_t len = strlen(s)+1;
	std::shared_ptr<char[]> ptr(new char[len]);
	strcpy(ptr.get(), s);
	return ptr; 
}

TEST(whitebox, mk_integer_001)
{
	integer  myInt;
	
	value y = mk_integer(1);
	EXPECT_TRUE(IsSmallInt(y));

	EXPECT_EQ(mk_integer(1),  reinterpret_cast<void*>(3)); // funky pointer stuff for small integer values
 	EXPECT_EQ(reinterpret_cast<intptr_t>(mk_integer(-1)),
						static_cast<intptr_t>(-1)); 
}
	
TEST(whitebox, mk_integer_002)
{
}

	extern "C" char* get_line(void); 

TEST(whitebox, expr_001)
{
	//                                1 11 111
	//                      01234567890 12 345
	auto input = mk_string("#stripped \".\" /\n");
	tx        = input.get() + 0;
	first_col = tx; 
	ceol      = tx + 15;
	char *q   = tx + 13;
	expr(q); 
}
// TEST(whitebox, singexpr_001)
// {
// 	first_col= tx= get_line(); 
// 
// 	parsetree  tree = singexpr(first_col);
// }

// TEST(whitebox, mk_rat_001)
// {
//   rational r = mk_rat(2, 2, 1, true);
// }

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

