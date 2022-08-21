//
// Created by andreas on 21.08.22.
//
#include <array>
#include <vector>
#include <numeric>
#include <iostream>

std::array<int, 5> get_digits(int number)
{
	auto result = std::array<int, 5>();
	for(int i=0; i < 5; ++i) {
		int digit = number % 10;
		number /= 10;
		result[i] = digit;
	}
	return result;
}

int fifth_power(int i)
{
	return i*i*i*i*i;
}

int fifth_power_digits_sum()
{
	int result{};
	for(int number =2; number < 400000; ++number )
	{
		auto digits = get_digits(number);
		int sum{};
		for(const auto & element: digits)
		{
			sum+= fifth_power(element);

		}
		if(sum == number) {
			std::cout << sum << "   " <<number << std::endl;
			result+=number;
		}
	}
	return result;
}


int main()
{
	std::cout << fifth_power_digits_sum() << std::endl;
//	auto test = get_digits(10000);
//	for(int i=0; i < 5; ++i)
//	{
//		std::cout << test[i] << std::endl;
//	}
}