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
	std::string big_int1_times_big_int2
		{"21732593723759235407399765787370415333957046911250030416004483672888629718439465421083217"};
	std::string big_int1_times_big_int3
		{"927673516296006980729894560881502774070244898464224480249709981742727683326165883231534258393132962111"};
	std::string big_int2_times_big_int3
		{"234200008968472643897563759490017090900853806121255762546487800286933351961031909024365909260379740965737038749477505295498821329328327"};
};

TEST_F(SetupBigIntegersMultiplication, test_multiplication_number1_times_number2)
{
	auto result = BigInteger<10>(number1) * BigInteger<10>(number2);
	EXPECT_TRUE(result.to_number_string() == number1_times_number2);
}

TEST_F(SetupBigIntegersMultiplication, test_multiplication_big_int1_times_big_int2)
{
	auto result = big_int1 * big_int2;
	EXPECT_TRUE(result.to_number_string() == big_int1_times_big_int2);
}

TEST_F(SetupBigIntegersMultiplication, test_multiplication_big_int1_times_big_int3)
{
	auto result = big_int1 * big_int3;
	EXPECT_TRUE(result.to_number_string() == big_int1_times_big_int3);
}

TEST_F(SetupBigIntegersMultiplication, test_multiplication_big_int2_times_big_int3)
{
	auto result = big_int2 * big_int3;
	EXPECT_TRUE(result.to_number_string() == big_int2_times_big_int3);

}
