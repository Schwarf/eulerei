//
// Created by andreas on 23.08.22.
//
#include "./../helpers/compute_primes.h"
#include <algorithm>

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

int to_number(std::vector<int> & digits)
{
	int result{digits[3]};
	for(int i=0; i < 3; --i)
	{
		result = digits[i] * 10 *(3 - i) ;
	}
	return result;
}


int main()
{
	std::unordered_set<int> primes;
	compute_primes_up_to_n(10000, primes);
	std::vector<int> result(3, 0);
	bool done =false;
	for (int i = 1000; i < 10000; ++i) {
		if(primes.find(i) != primes.end())
		{

			auto digits = get_vector(i);
			int count = 2;
			result[count] = i;
			while(true) {
				if (std::next_permutation(digits.begin(), digits.end())) {
					if(primes.find(to_number(digits)) != primes.end()) {
						count--;
						result[count] = to_number(digits);
					}
				}
				if(!count) {
					done = true;
					break;
				}
			}
		}
		if(done)
			break;
	}
	return 0;
}