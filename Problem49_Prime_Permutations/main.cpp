//
// Created by andreas on 23.08.22.
//
#include "./../helpers/compute_primes.h"
#include "./../helpers/permutations.h"
#include <iostream>
#include <set>


int main()
{
	int limit = 10000;
	std::vector<int> primes;
	compute_primes_up_to_n(limit, primes);
	std::set<int> result;
	int count{};
	int value1{};
	int value2{};
	for (int i =0; i < primes.size(); ++i) {
		value1 = primes[i];
		if(value1 < 1000)
			continue;
		for (int j = i+1; j < primes.size(); ++j) {
			{
				value2 = primes[j];
				if(value2 < 1000)
					continue;
				auto k = -value1 + 2*value2;
				if ( k < limit && std::find(primes.begin(), primes.end(), k) != primes.end() &&
					are_permutations_from_each_other(value1, value2) &&
					are_permutations_from_each_other(value1, k)) {
					std::cout << std::to_string(value1) + std::to_string(value2) + std::to_string(k) << std::endl;
				}

			}

		}
	}
	return 0;
}