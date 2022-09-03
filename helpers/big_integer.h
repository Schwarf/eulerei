//
// Created by andreas on 02.09.22.
//

#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H
#include <cstddef>
#include <string>
#include <bitset>
#include <utility>
#include <algorithm>
#include <iostream>
#include <array>

template<size_t number_of_bits>
class BigInteger
{
public:

	BigInteger(long long initial_value)
	{
		if (initial_value < 0) {
			initial_value = -initial_value;
			is_negative_ = true;
		}
		absolute_value_ = std::bitset<number_of_bits>(initial_value);
	}
	BigInteger(const std::string &initial_value)
	{
		absolute_value_ = convert_string_to_bitset(initial_value);
	}

	BigInteger(const std::bitset<number_of_bits> &initial_absolute_value, bool is_negative)
		:
		absolute_value_(initial_absolute_value),
		is_negative_(is_negative)
	{
	}

	std::string validate_string_and_determine_sign(const std::string &str)
	{
		if (str.empty()) {
			std::cerr << "BigInteger: String is empty" << std::endl;
		}
		auto sign = str[0];
		if (!std::isdigit(sign) && sign != '-') {
			std::cerr << "BigInteger: First character in string is neither number nor 'minus' sign but: " << str
					  << std::endl;
		}
		int first_digit_position{};
		if (sign == '-') {
			if (str.size() < 2)
				std::cerr << "BigInteger: String contains only a minus sign: " << str << std::endl;
			is_negative_ = true;
			first_digit_position = 1;
		}
		if (str[first_digit_position] == 0) {
			std::cerr << "BigInteger: Leading zero in string detected: " << str << std::endl;
		}
		if (!std::all_of(str.cbegin() + first_digit_position, str.cend(), [](char c)
		{ return std::isdigit(c); })) {
			std::cerr << "BigInteger: String contains non-numeric values: " << str << std::endl;
		}
		return str.substr(first_digit_position);
	}

private:
	std::bitset<number_of_bits> convert_string_to_bitset(const std::string & str)
	{

		auto absolute_value_string = validate_string_and_determine_sign(str);
		int digit{};
		int bit_index{};
		std::bitset<number_of_bits> result;
		int last_character_index = absolute_value_string.size() - 1;
		while (last_character_index > -1) {
			digit =  absolute_value_string[last_character_index--] - '0' ;
			result[bit_index++] = is_odd_decimal_digit_[digit];
			absolute_value_string = divide_string_decimal_number_by_2(absolute_value_string);
		}
		return result;
	}
	std::string divide_string_decimal_number_by_2(const std::string & input)
	{
		std::string result;
		int quotient{};
		// if we divide e.g. {10, 30, 50, 70, 90,} we get {5, 15, ... } with a 5 on the following digit.
		// for {0, 20, 40, ...} this is not the case
		int carry_over_five_or_zero {};
		int digit {};
		for(const auto & character: input)
		{
			digit = character -'0';
			quotient = digit /2 + carry_over_five_or_zero;
			carry_over_five_or_zero = is_odd_decimal_digit_[digit] ? 5 : 0;
			result += '0'+quotient;
		}
		result.erase(0, result.find_first_not_of('0'));
		return result;
	}

	bool is_negative_{false};
	std::bitset<number_of_bits> absolute_value_;
	static constexpr std::array<int, 10> is_odd_decimal_digit_{0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
};


#endif //BIG_INTEGER_H
