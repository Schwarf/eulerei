//
// Created by andreas on 22.08.22.
//


#include "./../helpers/get_all_divisors.h"
#include <unordered_map>
#include <numeric>
#include <iostream>


int main()
{
	std::unordered_map<int, int> help;
	for(int i{1}; i< 10000; ++i)
	{
		auto divisors = get_all_divisors(i);
		help[i] = std::accumulate(divisors.begin(), divisors.end(), 0);
	}
	int sum{};int count{};
	for(int i{1}; i < 10000; ++i)
	{
		if(help.find(help[i]) != help.end()  && help[help[i]] == i &&  help[i] != i)
		{
			count++;
			sum += help[i] + i;
			std::cout << i << "  " << help[i] << std::endl;
		}
	}
	std::cout << count << std::endl;
	std::cout << sum/2 << std::endl;

}