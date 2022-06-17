//
// Created by andreas on 12.06.22.
//
#include <vector>
#include <iostream>

int max_sequence_length(int max_value,int & number_with_max_sequence_length)
{
	int sequence_length{};
	int max_sequence_length{};

	for(int number = max_value; number > 1; --number)
	{
		// max_sequence_length is number-1
		if(max_sequence_length >= number)
			break;
		auto found_remainders = std::vector<int>(max_value);
		int nominator{1};
		int position{0};
		while(found_remainders[nominator] == 0 && nominator != 0)
		{
			found_remainders[nominator] = position;
			nominator *= 10;
			nominator %= number;
			position++;
		}
		sequence_length = position - found_remainders[nominator];
		if(sequence_length > max_sequence_length) {
			max_sequence_length = sequence_length;
			number_with_max_sequence_length = number;
		}

	}
	return max_sequence_length;
}



int main()
{
	int number{};
	std::cout << max_sequence_length(7, number) << std::endl;
	std::cout << number << std::endl;
}
