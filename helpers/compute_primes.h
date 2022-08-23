//
// Created by andreas on 21.08.22.
//

#ifndef COMPUTE_PRIMES_H
#define COMPUTE_PRIMES_H
#include <unordered_set>
#include <vector>
template<typename T>
void compute_primes_up_to_n(T n, std::unordered_set<T> & primes)
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

#endif //COMPUTE_PRIMES_H
