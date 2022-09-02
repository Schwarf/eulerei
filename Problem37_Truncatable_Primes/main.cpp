//
// Created by andreas on 21.08.22.
//
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <algorithm>
#include "./../helpers/compute_primes.h"

int main()
{
	std::unordered_set<int64_t> primes;
	compute_primes_up_to_n<int64_t>(1000000, primes);
	long sum {};
	int count{};
	for(const auto & element: primes)
	{
		if(element < 10)
			continue;
		auto number = element;
		std::vector<long> digits;
		int exponent{1};
		bool is_relevant{true};
		do
		{
			auto digit = number % 10;
			digits.push_back(digit);
			number /=10;
			if(number > 0 && primes.find(number) == primes.end())
			{
				is_relevant = false;
				break;
			}
		}while(number !=0);
		if(!is_relevant)
			continue;
		int revert_number {};

		exponent = 1;
		for(const auto & digit : digits)
		{
			revert_number += digit *exponent;
			if(primes.find(revert_number) == primes.end())
			{
				is_relevant = false;
				break;
			}
			exponent *=10;

		}
		if(!is_relevant)
			continue;
		count++;
		sum += element;
	}

	std::vector<int> test{-1,2,3,4,4,5};
	auto b = std::all_of(test.begin()+1, test.end(), [](int x){return x > 0;});
	std::cout << "All of " << b << std::endl;
	std::cout << sum << std::endl;
	std::cout << count << std::endl;
}