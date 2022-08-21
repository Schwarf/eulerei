#include <iostream>
#include <unordered_set>
#include <vector>
#include "./../helpers/compute_primes.h"


void f_n(std::unordered_set<int64_t> & primes, int64_t a, int64_t b, int & max_consecutive_primes, int64_t & product)
{
	int n{};
	int candidate{};
	int local_max{};
	for(n=0; n < 1001; n++)
	{
		candidate = n*n + a*n +b;
		if(primes.find(candidate) != primes.end())
		{
			local_max++;
			if (local_max > max_consecutive_primes) {
				max_consecutive_primes = local_max;
				product = a*b;
			}
		}
		else
			return;
	}
	if(n==1000)
		std::cout << "REACHED LIMIT OF n" << std::endl;
}


int main()
{
	std::unordered_set<int64_t> primes;
	compute_primes_up_to_n<int64_t>(2100000, primes);
	int max_consecutive_primes{};
	int64_t product{};
	for(int a = -999;  a < 1000; ++a)
	{
		for(int b = -1000;  b < 1001; ++b)
		{
			f_n(primes, a, b, max_consecutive_primes, product);
		}
	}
	std::cout << max_consecutive_primes << "  " << product << std::endl;
	return 0;
}
