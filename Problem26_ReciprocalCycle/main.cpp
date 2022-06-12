//
// Created by andreas on 12.06.22.
//
#include <deque>
#include <iostream>

int count_length_of_recurring_cycle(int numerator, int denominator, std::deque<int> & cycle, bool init, int & max_size)
{

	int res = numerator/denominator;
	if(!init && res ==0)
		return 0;
	if(cycle.front() == res)
	{
		cycle.pop_front();
	}
	else if(!init) {
		cycle.push_back(res);
		max_size =std::max(max_size, (int)cycle.size());
	}
	if(!init && cycle.empty())
		return max_size;

	numerator = (numerator % denominator)*10;
	count_length_of_recurring_cycle(numerator, denominator, cycle, false, max_size);

}



int main()
{
	std::deque<int> help;
	int max_size{};
	for(int i =2; i < 11; ++i)
		std::cout<< count_length_of_recurring_cycle(1, i, help, true, max_size) << std::endl;
	return 0;
}
