//
// Created by andreas on 23.08.22.
//

#ifndef PERMUTATIONS_H
#define PERMUTATIONS_H
#include <vector>
#include <algorithm>
#include <numeric>

template <typename T>
std::vector<std::vector<T>> get_permutations(std::vector<T> & input)
{
	std::sort(input.begin(), input.end());
	std::vector<std::vector<T>> result;
	do {
		result.push_back(input);
	} while(std::next_permutation(input.begin(), input.end()));
	return result;
}

template <typename T>
bool are_permutations_from_each_other(T number1, T number2 )
{
	auto digit_counter = std::vector<int>(10,false);
	T temp =number1;
	while(temp > 0)
	{
		digit_counter[temp % 10]++;
		temp /= 10;
	}
	temp =number2;
	while(temp > 0)
	{
		digit_counter[temp % 10]--;
		temp /= 10;
	}
	if(std::accumulate(digit_counter.begin(), digit_counter.end(), 0) > 0)
		return false;
	return true;
}



#endif //PERMUTATIONS_H
