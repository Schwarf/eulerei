//
// Created by andreas on 30.08.22.
//
#include <iostream>
#include "./../helpers/big_integer.h"

std::string alternative(){
    auto sum =  BigInteger<10100>();

    for(int i=1; i < 1001; ++i) {
        auto summand = BigInteger<10100>(i);
        sum += summand.to_power(i);
        std::cout << "i = " << i << std::endl;
    }
    std::cout << sum.to_number_string() << std::endl;
}


int main()
{
	long int result{};
	long int modulo = 10000000000;
	for(int i=1; i < 1001; ++i) {
		int long help{i};
		for (int j = 1; j < i ; ++j)
		{
			help *=i;
			if(help >= INT64_MAX/1000)
				help %= modulo;
		}
		result += help;
		result %= modulo;
	}
	std::cout << result << std::endl;
    auto test = alternative();
}