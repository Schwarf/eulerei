//
// Created by andreas on 02.09.22.
//

#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H
#include <cstddef>
#include <string>
#include <bitset>
#include <utility>
#include <algorithm>
#include <iostream>
#include <array>

constexpr static std::array<int, 10> IS_ODD_DECIMAL_DIGIT_ = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1};

template<size_t number_of_bits>
class BigInteger
{
public:

	BigInteger() = delete;

	explicit BigInteger(long long initial_value)
	{
		if (initial_value < 0) {
			initial_value = -initial_value;
			is_negative_ = true;
		}
		absolute_value_ = std::bitset<number_of_bits>(initial_value);
	}
	explicit BigInteger(const std::string &initial_value)
	{
		absolute_value_ = convert_string_to_bitset(initial_value);
	}

	explicit BigInteger(const std::bitset<number_of_bits> &initial_absolute_value, bool is_negative)
		:
		absolute_value_(initial_absolute_value),
		is_negative_(is_negative)
	{
	}
	// Copy constructor
	BigInteger(const BigInteger<number_of_bits> &other)
		:
		absolute_value_(other.absolute_value_),
		is_negative_(other.is_negative_)
	{
	}

	// Assignment operators
	BigInteger &operator=(const BigInteger<number_of_bits> &other)
	{
		if (this == other)
			return *this;
		absolute_value_ = other.absolute_value_;
		is_negative_ = other.is_negative_;
		return *this;

	}

	// Equal operator
	bool operator==(const BigInteger<number_of_bits> &rhs)
	{
		return are_equal(*this, rhs);
	}

	BigInteger<number_of_bits> &operator+(const BigInteger<number_of_bits> &rhs)
	{
		BigInteger<number_of_bits> result;
		addition(this->absolute_value_, rhs.absolute_value_);
	}

	std::string validate_string_and_determine_sign(const std::string &str)
	{
		if (str.empty()) {
			throw std::invalid_argument("BigInteger: String is empty");
		}
		auto sign = str[0];
		if (!std::isdigit(sign) && sign != '-') {
			throw std::invalid_argument(
				"BigInteger: First character in string is neither number nor 'minus' sign but: " + str);
		}
		int first_digit_position{};
		if (sign == '-') {
			if (str.size() < 2)
				throw std::invalid_argument("BigInteger: String contains only a minus sign: " + str);
			is_negative_ = true;
			first_digit_position = 1;
		}
		if (str[first_digit_position] == '0') {
			throw std::invalid_argument("BigInteger: Leading zero in string detected: " + str);
		}
		if (!std::all_of(str.cbegin() + first_digit_position, str.cend(), [](char c)
		{ return std::isdigit(c); })) {
			throw std::invalid_argument("BigInteger: String contains non-numeric values: " + str);
		}
		return str.substr(first_digit_position);
	}

	std::string to_binary_string()  {
		return absolute_value_.to_string();
	}

	std::string to_number_string()  {
		return to_decimal_string(absolute_value_);
	}


private:
	int first_bit_from_left(const std::bitset<number_of_bits> &value)
	{
		int index = value.size() - 1;
		while (index > -1 && !value.test(index))
			index--;
		return index;
	}

	void addition(std::bitset<number_of_bits> b1, std::bitset<number_of_bits> b2,
				  std::bitset<number_of_bits> &result)
	{
		int carry_over;
		for(int i=0; i < number_of_bits; ++i)
		{
			result[i] = b1[i] ^ b2[i] ^ carry_over;
			carry_over = ((b1[i] & b2[i]) | (b1[i] & carry_over)) | (b2[i] & carry_over);
		}
	}

	std::string to_decimal_string(std::bitset<number_of_bits> value) {
		constexpr int base = 10;
		std::string result{};
		// Using the doubling method we iterate from left to right. While moving right double
		// the digit result and if bit is set, add 1.
		// Whenever we are above base=10 we determine the digit by subtracting 10 and set the
		// remainder
		unsigned int digit{};
		std::bitset<number_of_bits> remainder; // Temp holder of divide value
		do {
			digit = 0;
			remainder.reset();
			for(int i = value.size(); i > -1; i--) {

				digit = digit * 2 + value[i];
				if (digit >= base) {
					digit -= base;
					remainder[i] = 1;
				} else {
					remainder[i] = 0;
				}
			}
			value = remainder;
			result.insert(0, 1, '0' + digit);

		} while (value.any());

		return (is_negative_ ? "-" + result : result);
	}


	void subtraction(std::bitset<number_of_bits> b1, std::bitset<number_of_bits> b2)
	{

	}

	bool are_equal(const BigInteger<number_of_bits> &left_hand_side, const BigInteger<number_of_bits> &right_hand_side)
	{
		if (left_hand_side.is_negative_ != right_hand_side.is_negative_)
			return false;
		for (int i = 0; i < number_of_bits; ++i) {
			if (right_hand_side.absolute_value_[i] != left_hand_side.absolute_value_[i])
				return false;
		}
		return true;
	}

	std::bitset<number_of_bits> convert_string_to_bitset(const std::string &str)
	{
		auto absolute_value_string = validate_string_and_determine_sign(str);
		int digit{};
		int bit_index{};
		std::bitset<number_of_bits> result;
		while (!absolute_value_string.empty()) {
			digit = absolute_value_string.back() - '0';
			// instead of 'modulo 2' operation we just set the bits for odd decimal digits
			result[bit_index++] = IS_ODD_DECIMAL_DIGIT_[digit];
			absolute_value_string = divide_string_decimal_number_by_2(absolute_value_string);
		}
		return result;
	}

	std::string divide_string_decimal_number_by_2(const std::string &input)
	// we divide starting from the most significant (leftmost) digit
	{
		std::string result;
		int quotient{};
		// if we divide e.g. {10, 30, 50, 70, 90,} we get {5, 15, ... } with a 5 on the following digit.
		// for {0, 20, 40, ...} this is not the case
		int carry_over_five_or_zero{};
		int digit{};
		for (const auto &character: input) {
			digit = character - '0';
			quotient = digit / 2 + carry_over_five_or_zero;
			carry_over_five_or_zero = IS_ODD_DECIMAL_DIGIT_[digit] ? 5 : 0;
			result += '0' + quotient;
		}
		result.erase(0, result.find_first_not_of('0'));
		return result;
	}

	bool is_negative_{false};
	std::bitset<number_of_bits> absolute_value_;
};


#endif //BIG_INTEGER_H
