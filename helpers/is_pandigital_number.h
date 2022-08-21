//
// Created by andreas on 21.08.22.
//

#ifndef IS_PANDIGITAL_NUMBER_H
#define IS_PANDIGITAL_NUMBER_H
bool is_pandigital(int n) {
	int digits = 0;
	int count = 0;
	int tmp;

	while (n > 0) {
		tmp = digits;
		digits = digits | 1 << (int)((n % 10) - 1);
		if (tmp == digits) {
			return false;
		}

		count++;
		n /= 10;
	}
	return digits == (1 << count) - 1;
}

#endif //IS_PANDIGITAL_NUMBER_H
