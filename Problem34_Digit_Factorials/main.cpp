//
// Created by andreas on 21.08.22.
//
#include <array>
#include <iostream>

std::array<int, 10> factorial()
{
	std::array<int, 10> result{1, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	for (int i=1; i < 10; ++i)
	{
		auto j = i-1;
		while(j) {
			result[i] *= j--;
		}
	}
	return result;
}

int main()
{
	auto fact = factorial();
	int result{};
	for(int i{3}; i < 100000000; ++i)
	{
		auto number = i;
		int sum{};
		while(number != 0)
		{
			auto digit = number % 10;
			sum += fact[digit];
			number /= 10;
		}
		if(sum == i) {
			result += i;
			std::cout << sum << std::endl;
		}
	}
	std::cout << result << std::endl;

}