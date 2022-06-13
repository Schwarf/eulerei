//
// Created by andreas on 12.06.22.
//
#include <vector>
#include <iostream>

void count_length_of_recurring_cycle(int numerator, int denominator, std::vector<int> & cycle)
{
	int depth{};
	while(numerator != 0)
	{
		int res = numerator/denominator;
		cycle.push_back(res);
		numerator = (numerator % denominator)*10;
		depth++;
		if(depth ==1000)
			break;
	}
}



int main()
{

	int max_size{};
	int count{};
	for(int i =2; i < 1000; ++i) {
		std::vector<int> help;
		count_length_of_recurring_cycle(1, i, help);
		if(help.size() ==1000)
		{
			count++;
			std::cout << i << std::endl;
		}
	}
	std::cout << "count " << count << std::endl;
	return 0;
}
