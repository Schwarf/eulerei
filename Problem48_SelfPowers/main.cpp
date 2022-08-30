//
// Created by andreas on 30.08.22.
//
#include <iostream>
#include <limits>
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
}