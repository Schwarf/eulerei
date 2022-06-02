#include <iostream>
#include <unordered_set>
#include <vector>


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
	compute_primes_up_to_n(2100000, primes);
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
