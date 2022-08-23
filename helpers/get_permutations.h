//
// Created by andreas on 23.08.22.
//

#ifndef GET_PERMUTATIONS_H
#define GET_PERMUTATIONS_H
#include <vector>
#include <algorithm>

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


#endif //GET_PERMUTATIONS_H
