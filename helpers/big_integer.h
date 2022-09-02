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

template <size_t bit_size>
class BigInteger
{
public:

	BigInteger(long long initial_value){
		if(initial_value < 0) {
			initial_value = -initial_value;
			is_negative_ = true;
		}
		value_ = std::bitset<bit_size>(initial_value);
	}
	BigInteger(const std::string & initial_value)
	{
		value_ = convert_string_to_bitset(initial_value);
	}



private:
	std::bitset<bit_size> convert_string_to_bitset(const std::string str)
	{
		validate_string(str);

	}
	void validate_string(const std::string & str)
	{
		if(str.empty()) {
			std::cerr << "String is empty" << std::endl;
		}
		auto sign = str[0];
		if(!std::isdigit(sign) && sign != '-') {
			std::cerr << "First character in string is neither number nor 'minus' sign but " << sign << std::endl;
		}
		int first_digit_position{};
		if(sign == '-') {
			is_negative_ = true;
			first_digit_position =1;
		}
		if(!std::all_of(str.cbegin()+first_digit_position, str.cend(), [](char c) { return std::isdigit(c); })) {
			std::cerr << "String contains non-numeric values!!!!" << std::endl;
		}

	}
	bool is_negative_{false};
	std::bitset<bit_size> value_;
};


#endif //BIG_INTEGER_H
