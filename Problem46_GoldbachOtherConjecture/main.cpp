//
// Created by andreas on 02.06.22.
//
#include <iostream>
#include <unordered_set>
#include <algorithm>
#include "./../helpers/compute_primes.h"




int main()
{
	std::unordered_set<int> primes;
	int n= 10000;
	compute_primes_up_to_n(n, primes);
	for(int i =33; i < 10000; i+=2)
	{
		if(primes.find(i) != primes.end())
			continue;

	}
	return 0;
}