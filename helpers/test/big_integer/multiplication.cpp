//
// Created by andreas on 08.09.22.
//
//
// Created by andreas on 04.09.22.
//

#include "gtest/gtest.h"
#include "./../../big_integer.h"

class SetupBigIntegersMultiplication: public testing::Test
{
protected:
	std::string big_number1{"9278118309180938109380983109"};
	std::string big_number2{"2342349278113243248309180938234234109380983109572387399309213"};
	std::string big_number3{"99985092384309223098482340923184482309480342341093809831372189479238438579"};
	std::string number1{"17"};
	std::string number2{"9"};
	std::string number1_times_number2{"153"};
	BigInteger<1000> big_int1 = BigInteger<1000>(big_number1);
	BigInteger<1000> big_int2 = BigInteger<1000>(big_number2);
	BigInteger<1000> big_int3 = BigInteger<1000>(big_number3);

};

TEST_F(SetupBigIntegersMultiplication, test_multiplication_)
{
	auto result = BigInteger<10>(number1) * BigInteger<10>(number2);
	EXPECT_TRUE(result.to_number_string() == number1_times_number2);
}

