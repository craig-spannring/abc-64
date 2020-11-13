#include <iostream>
#include <string>
#include <unistd.h>

#include "gtest/gtest.h"

TEST(whitebox, 
{
	ASSERT_DOUBLE_EQ(1.0, 1.00000000000000);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

