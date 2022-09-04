//
// Created by andreas on 03.09.22.
//
#include <iostream>
#include "big_integer.h"
int main()
{
	std::string s1{"9278118309180938109380983109"};
	auto x = BigInteger<1000>(s1);

	std::string input{"11823901840948239058230923095823095823091"};
	auto z = BigInteger<1000>(input);

	std::cout << z.to_number_string() << std::endl;
	auto y = x+z;
	std::cout << (y.to_number_string()) << std::endl;

	return 0;
}