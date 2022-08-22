//
// Created by andreas on 22.08.22.
//

#include <iostream>
// n = (dimension -1)/2
int answer(int n)
{
	n = (n-1)/2;
	//auto upper_right_quadrant = 4 * n * n + 4 * n + 1;
	//auto lower_left_quadrant = 4 * n * n + 1;
	//auto lower_right_quadrant = 4 * n * n - 2 * n + 1;
	//auto upper_left_quadrant = 4 * n * n + 2 * n + 1;
	//Sum above formulas from 1..n  (add 1 for center value)
	return 2 * n * (8 * n * n + 15 * n + 13) / 3 + 1;
}

int main()
{
	std::cout << answer(1001) << std::endl;
}