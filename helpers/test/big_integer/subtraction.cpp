//
// Created by andreas on 05.09.22.
//
#include "gtest/gtest.h"
#include "./../../big_integer.h"

class SetupBigIntegersSubtraction: public testing::Test
{
protected:
	std::string big_number1{"9278118309180938109380983109"};
	std::string big_number2{"2342349278113243248309180938234234109380983109572387399309213"};
	std::string big_number3{"99985092384309223098482340923184482309480342341093809831372189479238438579"};
	std::string big_number1_plus_2{"2342349278113243248309180938234243387499292290510496780292322"};
	std::string big_number2_plus_3{"99985092384311565447760454166432791490418576575203190814481761866637747792"};
	std::string number1{"17"};
	std::string number2{"9"};
	std::string number1_minus_number2{"8"};
	std::string number2_minus_number1{"-8"};
	BigInteger<1000> big_int1 = BigInteger<1000>(big_number1);
	BigInteger<1000> big_int2 = BigInteger<1000>(big_number2);
	BigInteger<1000> big_int3 = BigInteger<1000>(big_number3);

};


TEST_F(SetupBigIntegersSubtraction, test_addition_number1_minus_number2)
{
	auto result = BigInteger<10>(number1) - BigInteger<10>(number2) ;
	EXPECT_TRUE(result.to_number_string() == number1_minus_number2);
	result = BigInteger<10>(number2) - BigInteger<10>(number1);\
	std::cout << result.to_binary_string() << std::endl;
	EXPECT_TRUE(result.to_number_string() == number2_minus_number1);
}
