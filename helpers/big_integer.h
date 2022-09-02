//
// Created by andreas on 02.09.22.
//

#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H
#include <cstddef>
#include <string>
#include <bitset>

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
		
	}

	bool is_negative_{false};
	std::bitset<bit_size> value_;
};


#endif //BIG_INTEGER_H
