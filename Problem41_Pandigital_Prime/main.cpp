//
// Created by andreas on 21.08.22.
//
#include <iostream>
#include <vector>
#include <unordered_set>
#include "../helpers/compute_primes.h"

int main()
{
	std::unordered_set<int64_t> primes;
	int64_t top = 987654322;
	compute_primes_up_to_n(top, primes);
	int64_t max{};

	for(const auto & element : primes)
	{
		int64_t number = element;
		std::vector<bool> digits(10, false);
		bool is_relevant = true;
		while(number !=0)
		{
			auto digit = number % 10;

			if(digit ==0 || digits[digit])
			{
				is_relevant = false;
				break;
			}
			digits[digit] = true;
			number /=10;

		}
		if(!is_relevant)
			continue;
		for(int i=1; i < 10; ++i)
		{
			if(!digits[i])
			{
				is_relevant = false;
				break;
			}
		}
		if(!is_relevant)
			continue;
		max = std::max(element, max);
	}
	std::cout << max << std::endl;

	return 0;
}