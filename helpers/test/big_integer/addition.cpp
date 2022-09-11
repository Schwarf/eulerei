//
// Created by andreas on 04.09.22.
//

#include "gtest/gtest.h"
#include "./../../big_integer.h"

class SetupBigIntegersAddition : public testing::Test {
protected:
    std::string big_number1{"9278118309180938109380983109"};
    std::string big_number2{"2342349278113243248309180938234234109380983109572387399309213"};
    std::string big_number3{"99985092384309223098482340923184482309480342341093809831372189479238438579"};
    std::string big_number4{"-113243248327389789209180938234234109380983109572387399309213"};
    std::string big_number1_plus_2{"2342349278113243248309180938234243387499292290510496780292322"};
    std::string big_number2_plus_3{"99985092384311565447760454166432791490418576575203190814481761866637747792"};
    std::string big_number1_plus_4{"-113243248327389789209180938234224831262673928634278018326104"};

    std::string number1{"17"};
    std::string number2{"9"};
    std::string number1_plus_number2{"26"};
    BigInteger<1000> big_int1 = BigInteger<1000>(big_number1);
    BigInteger<1000> big_int2 = BigInteger<1000>(big_number2);
    BigInteger<1000> big_int3 = BigInteger<1000>(big_number3);
    BigInteger<1000> big_int4 = BigInteger<1000>(big_number4);

};

TEST_F(SetupBigIntegersAddition, test_addition_big_number1_plus_big_number2) {
    auto result = big_int1 + big_int2;
    EXPECT_TRUE(result.to_number_string() == big_number1_plus_2);
}

TEST_F(SetupBigIntegersAddition, test_addition_big_number2_plus_big_number3) {
    auto result = big_int2 + big_int3;
    EXPECT_TRUE(result.to_number_string() == big_number2_plus_3);
}

TEST_F(SetupBigIntegersAddition, test_addition_big_number1_plus_big_number4) {
    auto result = big_int1 + big_int4;
    EXPECT_TRUE(result.to_number_string() == big_number1_plus_4);
    result = big_int4 + big_int1;
    EXPECT_TRUE(result.to_number_string() == big_number1_plus_4);
}


TEST_F(SetupBigIntegersAddition, test_addition_number1_plus_number2) {
    auto result = BigInteger<10>(number1) + BigInteger<10>(number2);
    EXPECT_TRUE(result.to_number_string() == number1_plus_number2);
}


TEST_F(SetupBigIntegersAddition, test_many_simple_numbers_via_string) {
    int start{10000000};
    auto addend1 = BigInteger<64>(start);
    for (int i = 1; i < 1000; ++i) {
        auto string = std::to_string(i);
        auto addend2 = BigInteger<64>(string);
        auto sum = addend1 + addend2;
        EXPECT_TRUE(sum.to_number_string() == std::to_string(i + start));
    }
}

TEST_F(SetupBigIntegersAddition, test_many_simple_numbers_via_string_negative) {
    int start{10000000};
    auto addend1 = BigInteger<64>(start);
    for (int i = 1; i < 1000; ++i) {
        auto string = std::to_string(-i);
        auto addend2 = BigInteger<64>(string);
        auto sum = addend1 + addend2;
        EXPECT_TRUE(sum.to_number_string() == std::to_string(-i + start));
    }
}
