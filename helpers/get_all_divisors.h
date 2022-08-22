//
// Created by andreas on 22.08.22.
//

#ifndef GET_ALL_DIVISORS_H
#define GET_ALL_DIVISORS_H
#include <vector>
template <typename T>
std::vector<T> get_all_divisors(T n)
{
	std::vector<T> result;
	for(T i=1; i < n /2 +1; ++i )
	{
		if( (n % i) == 0)
			result.push_back(i);
	}
	return result;
}


#endif //GET_ALL_DIVISORS_H
