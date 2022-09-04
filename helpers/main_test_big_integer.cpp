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

	auto t1 = BigInteger<10>("17");
	auto t2 = BigInteger<10>("9");
	auto e1 = t1 - t2;
	std::bitset<10> f(-25);
	std::cout << "t1 = " << f.size()<< std::endl;
	std::cout << f.to_string() << std::endl;
	std::cout << f[9] << std::endl;
	return 0;
}