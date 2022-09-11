//
// Created by andreas on 11.09.22.
//

#include "gtest/gtest.h"
#include "./../../big_integer.h"

class SetupBigIntegersEqualOperator : public testing::Test {
protected:
    std::string big_number1{"9278118309180938109380983109"};
    std::string big_number2{"-9278118309180938109380983109"};
    BigInteger<1000> big_int1 = BigInteger<1000>(big_number1);
    BigInteger<1000> big_int2 = BigInteger<1000>(big_number1);
    BigInteger<1000> big_int3 = BigInteger<1000>(big_number2);
    BigInteger<1000> big_int4 = BigInteger<1000>(big_number2);

};

TEST_F(SetupBigIntegersEqualOperator, test_equal_big_number1_equal_big_number2) {
    auto result = big_int1 == big_int2;
    EXPECT_TRUE(result);
    result = big_int1 == big_int3;
    EXPECT_FALSE(result);
    result = big_int3 == big_int4;
    EXPECT_TRUE(result);
}

TEST_F(SetupBigIntegersEqualOperator, test_unequal_big_number1_equal_big_number2) {
    auto result = big_int1 != big_int2;
    EXPECT_FALSE(result);
    result = big_int1 != big_int3;
    EXPECT_TRUE(result);
    result = big_int3 != big_int4;
    EXPECT_FALSE(result);
}