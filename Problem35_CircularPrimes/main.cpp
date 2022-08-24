//
// Created by andreas on 02.06.22.
//
#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include "./../helpers/compute_primes.h"

int main()
{
	std::unordered_set<int> primes;
	int n = 1000000;
	compute_primes_up_to_n(n, primes);
	int circular_primes{};
	for(const auto & prime: primes)
	{
		std::string p = std::to_string(prime);
		std::cout << " p= " << p << std::endl;
		bool is_circular{true};
		for(int i =0; i < p.size() +1; ++i)
		{
			auto h = p;
			std::rotate(h.begin(), h.begin()+i, h.end());
			if(primes.find(std::stoi(h)) == primes.end())
			{
				is_circular = false;
				break;
			}
		}
		if(is_circular)
			circular_primes++;
	}
	std::cout << circular_primes << std::endl;


}