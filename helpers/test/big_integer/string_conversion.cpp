//
// Created by andreas on 04.09.22.
//
#include <regex>
#include "gtest/gtest.h"
#include "./../../big_integer.h"

class SetupBigIntegersStringConversion : public testing::Test {
protected:
    std::string bad_string_with_letter{"927a09380983109"};
    std::string bad_string_with_symbol{"58!309"};
    std::string bad_string_with_letter_on_first_position{"a14"};
    std::string bad_string_with_leading_zero{"0509"};
    std::string good_string_negative{"-178"};
    std::string bad_string_negative_with_leading_zero{"-089378193572438572389478238947435435435"};
    std::string bad_string_negative_with_letter{"-572438578230948230948230941X"};
    std::string bad_string_only_minus_sign{"-"};
};

TEST_F(SetupBigIntegersStringConversion, string_with_letter) {
    try {
        auto test = BigInteger<100>(bad_string_with_letter);
        FAIL() << "Expected std::invalid_argument";
    }
    catch (std::invalid_argument const &error) {
        EXPECT_TRUE(std::regex_match(error.what(), std::regex("BigInteger: String contains non-numeric values: (.*)")));
    }

}

TEST_F(SetupBigIntegersStringConversion, string_with_letter_on_first_position) {
    try {
        auto test = BigInteger<100>(bad_string_with_letter_on_first_position);
        FAIL() << "Expected std::invalid_argument";
    }
    catch (std::invalid_argument const &error) {
        EXPECT_TRUE(std::regex_match(error.what(),
                                     std::regex(
                                             "BigInteger: First character in string is neither number nor 'minus' sign but: (.*)")));
    }

}

TEST_F(SetupBigIntegersStringConversion, string_with_symbol) {
    try {
        auto test = BigInteger<100>(bad_string_with_symbol);
        FAIL() << "Expected std::invalid_argument";
    }
    catch (std::invalid_argument const &error) {
        EXPECT_TRUE(std::regex_match(error.what(), std::regex("BigInteger: String contains non-numeric values: (.*)")));
    }

}

TEST_F(SetupBigIntegersStringConversion, string_with_leading_zero) {
    try {
        auto test = BigInteger<100>(bad_string_with_leading_zero);
        FAIL() << "Expected std::invalid_argument";
    }
    catch (std::invalid_argument const &error) {
        EXPECT_TRUE(std::regex_match(error.what(), std::regex("BigInteger: Leading zero in string detected: (.*)")));
    }

}


TEST_F(SetupBigIntegersStringConversion, string_negative_with_letter) {
    try {
        auto test = BigInteger<100>(bad_string_negative_with_letter);
        FAIL() << "Expected std::invalid_argument";
    }
    catch (std::invalid_argument const &error) {
        EXPECT_TRUE(std::regex_match(error.what(), std::regex("BigInteger: String contains non-numeric values: (.*)")));
    }

}

TEST_F(SetupBigIntegersStringConversion, string_negative_with_leading_zero) {
    try {
        auto test = BigInteger<100>(bad_string_negative_with_leading_zero);
        FAIL() << "Expected std::invalid_argument";
    }
    catch (std::invalid_argument const &error) {
        EXPECT_TRUE(std::regex_match(error.what(), std::regex("BigInteger: Leading zero in string detected: (.*)")));
    }

}

TEST_F(SetupBigIntegersStringConversion, string_only_minus_sign) {
    try {
        auto test = BigInteger<100>(bad_string_only_minus_sign);
        FAIL() << "Expected std::invalid_argument";
    }
    catch (std::invalid_argument const &error) {
        EXPECT_TRUE(std::regex_match(error.what(), std::regex("BigInteger: String contains only a minus sign: (.*)")));
    }

}
