//
// Created by andreas on 24.08.22.
//

#ifndef IS_POWER_OF_H
#define IS_POWER_OF_H
#include <cstddef>
#include <vector>
#include <algorithm>
template <size_t base, typename T>
std::vector<T> convert_to_base_ary(T value)
{
	std::vector<T> result;
	while(value)
	{
		result.push_back(value % base );
		value /= base;
	}
	return result;
}

template <size_t base, typename T>
bool is_power_of(T value)
{
	if (value <= 0)
		return false;
	if(base==2)
		return (value &(value-1)) ==0;

	auto conversion = convert_to_base_ary<base, T>(value);
	size_t i{2};
	if(std::count(conversion.begin(), conversion.end(), 1) > 1)
		return false;
	while(i < base)
	{
		if(std::find(conversion.begin(), conversion.end(), i) != conversion.end())
			return false;
		i++;
	}
	return true;
}

#endif //IS_POWER_OF_H
