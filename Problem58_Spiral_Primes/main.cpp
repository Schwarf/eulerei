//
// Created by andreas on 23.08.22.
//
#include "./../helpers/compute_primes.h"
#include <iostream>

int right_upper(int n)
{
	return 4 * n * n - 2 * n + 1;
}

int left_upper(int n)
{
	return 4 * n * n + 1;
}

int left_lower(int n)
{
	return 4 * n * n + 2 * n + 1;
}

int right_lower(int n)
{
	return 4 * n * n + 4 * n + 1;
}

int main()
{
	std::unordered_set<int> help;
	compute_primes_up_to_n(1000000000, help);
	int total{1};
	int count{};
	int side_length{1};
	int i{1};
	while(true) {
		total += 4;
		if (help.find(right_lower(i)) != help.end())
			count++;
		if (help.find(right_upper(i)) != help.end())
			count++;
		if (help.find(left_upper(i)) != help.end())
			count++;
		if (help.find(left_lower(i)) != help.end())
			count++;
		side_length += 2;
		std::cout << right_lower(i) << std::endl;
		i++;
		auto x = static_cast<double>(count) / static_cast<double>(total);
		std::cout << side_length << ", " << x << ", " << count << ", " << total << std::endl;
		if (x < 0.1)
			break;
	}
	std::cout << side_length << std::endl;


	return 0;
}