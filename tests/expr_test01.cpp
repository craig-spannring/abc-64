#include <iostream>
#include <string>
#include <unistd.h>
#include <memory>

#include "gtest/gtest.h"

#include "b.h"
#include "bobj.h"
#include "bint.h"
#include "i2par.h"
#include "i3int.h"
#include "b1mess.h"



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


TEST(whitebox, expr_test01)
{
	std::array<char, 100>   raw_buf_;
	char*  raw_buf = &raw_buf_[0];
	//                         11111 111 1 1
	//               012345678901234 567 8 9
	strcpy(raw_buf, "WRITE stripped \"ab\"\n");
	tx = raw_buf + 6;

	parsetree  w = expr(raw_buf + 19);
        EXPECT_TRUE(w!=nullptr); 
}
	       
int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	pre_init();
	init(); 
	return RUN_ALL_TESTS();
}

