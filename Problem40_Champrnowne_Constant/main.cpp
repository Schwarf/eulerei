//
// Created by andreas on 21.08.22.
//
#include <string>
#include <iostream>
#include "./../helpers/get_all_divisors.h"
int main()
{
	std::string help;
	help.reserve(1000001);
	for (int i = 1; i < 300000; ++i) {
		help += std::to_string(i);
	}
	std::cout << help.size() << std::endl;
	int result = std::stoi(help.substr(0, 1)) *
		std::stoi(help.substr(9, 1)) *
		std::stoi(help.substr(99, 1)) *
		std::stoi(help.substr(999, 1)) *
		std::stoi(help.substr(9999, 1)) *
		std::stoi(help.substr(99999, 1)) *
		std::stoi(help.substr(999999, 1));
	std::cout << result << std::endl;
}
