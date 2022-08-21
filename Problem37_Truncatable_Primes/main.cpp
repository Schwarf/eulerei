//
// Created by andreas on 21.08.22.
//
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <algorithm>
void compute_primes_up_to_n(int64_t n, std::unordered_set<int64_t> & primes)
{
	std::vector<bool> is_prime(n +1, true);
	is_prime[0] = false;
	is_prime[1] = false;
	for(int64_t i =2; i*i <= n; ++i)
	{
		if(is_prime[i])
		{
			for(int64_t j = i*i; j <= n; j+=i)
			{
				is_prime[j] = false;
			}
		}
	}
	for(int i=0; i <= n; ++i)
	{
		if(is_prime[i])
			primes.insert(i);
	}

}




int main()
{
	std::unordered_set<int64_t> primes;
	compute_primes_up_to_n(10000, primes);
	long sum {};
	for(const auto & element: primes)
	{
		if(element < 10)
			continue;
		int reverse{};
		auto number = element;
		std::vector<long> digits;
		int exponent{1};
		bool is_relevant{true};
		while(number != 0)
		{
			auto digit = number % 10;
			digits.push_back(digit);
			for(int i=1; i < digits.size(); ++i)
			{
				digit *=10;
			}
			number /=10;
			auto truncated = number - digit;
			if(primes.find(truncated) == primes.end())
			{
				is_relevant = false;
				break;
			}
		}
		if(!is_relevant)
			continue;
		int revert_number {};

		std::reverse(digits.begin(), digits.end());
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

		sum += element;
	}
	std::cout << sum << std::endl;
}