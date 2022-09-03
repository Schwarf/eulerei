//
// Created by andreas on 24.08.22.
//

#include "is_power_of.h"
#include <iostream>
#include <bitset>
#include <array>
constexpr std::array<char, 10> SX_THE_ODDS{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 };
std::string div2(std::string& dec_value) {

	int carry{};
	int adder{};
	std::string remainder{};

	for(auto& ch : dec_value) {
		carry = (ch - '0') / 2 + adder;
		adder = SX_THE_ODDS[(ch - '0')] * 5;
		remainder += '0' + carry;
	}
	remainder.erase(0, remainder.find_first_not_of('0'));
	return remainder;
}
int main()
{
	int x1=21, x2=12, x3=27;
	int y1=16, y2=12, y3=27;
	int z1 = 17*17, z2 = 17*16, z3 = 67890;
	std::cout << is_power_of<3, int>(x1) << std::endl;
	std::cout << is_power_of<3, int>(x2) << std::endl;
	std::cout << is_power_of<3, int>(x3) << std::endl;

	std::cout << is_power_of<4, int>(y1) << std::endl;
	std::cout << is_power_of<4, int>(y2) << std::endl;
	std::cout << is_power_of<4, int>(y3) << std::endl;

	for(int i{}; i < 1000; ++i)
	{
		if(is_power_of<17, int>(i))
			std::cout << i << std::endl;
	}
	std::string h{"17"};
	std::bitset<10> result;
	int digit{};
	int remainder{};
	int bit_index{};
	int last_character_index = h.size() - 1;
	while (last_character_index > -1) {
		digit = h[last_character_index--] - '0' + remainder;
		result[bit_index++] =  digit % 2;
		remainder = digit/2;
	}
	std::cout << result.to_ulong() << std::endl;

	std::cout << div2(h) <<std::endl;
	return 0;

}