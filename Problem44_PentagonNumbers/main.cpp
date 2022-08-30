//
// Created by andreas on 02.06.22.
//
#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>

std::unordered_set<long long int> compute_pentagon_numbers(int max )
{
	int count{1};
	std::unordered_set<long long int> result;

	while(count <= max)
	{
		result.insert(count*(3*count-1)/2);
		count++;
	}
	return result;
}




int main()
{
	std::vector<long long int> help;
	auto pentagon_numbers = compute_pentagon_numbers(3000);
	help.insert(help.end(), pentagon_numbers.begin(), pentagon_numbers.end());
	std::sort(help.begin(), help.end());
	std::vector<long long int> result;
	for(int i =0; i < help.size() -1; ++i)
	{
		for(int j =i; j < help.size(); ++j)
		{
			auto sum = help[i] + help[j];
			auto diff = help[j] - help[i];
			if(pentagon_numbers.find(sum) != pentagon_numbers.end() && pentagon_numbers.find(diff) != pentagon_numbers.end())
				result.push_back(diff);
		}

	}
	auto min = std::min_element(result.begin(), result.end());
	std::cout << *min << std::endl;
	return 0;
}


