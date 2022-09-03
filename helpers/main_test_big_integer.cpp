//
// Created by andreas on 03.09.22.
//
#include <iostream>
#include "big_integer.h"
int main()
{
	std::string s1{"127"};
	auto x = BigInteger<20>(s1);
	return 0;
}