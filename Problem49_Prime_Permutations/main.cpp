//
// Created by andreas on 23.08.22.
//
#include "./../helpers/compute_primes.h"
#include "./../helpers/get_permutations.h"
#include <iostream>
#include <set>

std::vector<int> get_vector(int n)
{
	std::vector<int> result;
	for(int i=0; i < 4; ++i)
	{
		result.push_back(n % 10);
		n /= 10;
	}
	return result;
}

int to_number(const std::vector<int> & digits)
{
	int result{digits[3]};
	int factor = 1000;
	for(int i=0; i < 3; ++i)
	{
		result += digits[i] * factor ;
		factor /=10;
	}
	return result;
}



int main()
{
	std::unordered_set<int> primes;
	compute_primes_up_to_n(10000, primes);
	bool done =false;
	std::set<int> result;
	int count{};
	for (int i = 1000; i < 10000; ++i) {
		if(primes.find(i) != primes.end())
		{
			auto digits = get_vector(i);
			auto permutations = get_permutations(digits);
			for(const auto & permutation : permutations)
			{
				if(permutation[0] == 0)
					break;
				auto number = to_number(permutation);
				if(primes.find(number) != primes.end() && number > i) {
					for (const auto & element : permutation)
						result.insert(number);
				}

			}
			if(result.size()==12)
				count++;
		}
	}
	for(const auto & element: result)
		std::cout << element << ", ";
	std::cout << "\n" << count ;
	return 0;
}