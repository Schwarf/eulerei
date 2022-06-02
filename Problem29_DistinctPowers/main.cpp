//
// Created by andreas on 02.06.22.
//
#include <set>
#include <cmath>
#include <iostream>
int main()
{
	std::set<double> distinct;
	for(int a = 2; a < 101; a++)
	{
		for(int b = 2; b < 101; b++)
		{
			double x = std::pow(static_cast<double>(a), static_cast<double>(b));
			distinct.insert(x);
		}
	}
	std::cout << distinct.size() << std::endl;

	return 0;
}