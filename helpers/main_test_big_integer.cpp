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
	auto z = -x;

	std::cout << z.to_number_string() << std::endl;
	auto y = x+z;
	std::cout << (y.to_number_string()) << std::endl;

	auto t1 = BigInteger<1000>("9");
	auto t2 = BigInteger<1000>("17");
	auto e1 = t1 + t2;
	std::cout << "z = " << z.to_number_string()<< std::endl;
	std::bitset<4000> f(25);
	std::cout << "t1 = " << f.size()<< std::endl;
	std::cout << f.to_string() << std::endl;
	std::cout << f[9] << std::endl;
	auto e2 = t1.to_power(17);
	std::cout << e2.to_number_string() << std::endl;

	return 0;
}