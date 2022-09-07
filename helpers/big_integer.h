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

// We work with 2's complement binary representation
template<size_t number_of_bits>
class BigInteger
{
public:

	explicit BigInteger()
	{
		std::bitset<number_of_bits>();
	}

	explicit BigInteger(long long initial_value)
	{
		value_in_twos_complement_representation_ = std::bitset<number_of_bits>(initial_value);
	}
	explicit BigInteger(const std::string &value)
	{
		value_in_twos_complement_representation_ = convert_string_to_bitset(value);
	}

	explicit BigInteger(const std::bitset<number_of_bits> &initial_value)
		:
		value_in_twos_complement_representation_(initial_value)
	{

	}
	// Copy constructor
	BigInteger(const BigInteger<number_of_bits> &other)
		:
		value_in_twos_complement_representation_(other.value_in_twos_complement_representation_)
	{
	}

	// Assignment operators
	BigInteger &operator=(const BigInteger<number_of_bits> &other)
	{
		value_in_twos_complement_representation_ = other.value_in_twos_complement_representation_;
		return *this;

	}
	bool is_negative()
	{
		return value_in_twos_complement_representation_[number_of_bits - 1];
	}

	// Equal operator
	bool operator==(const BigInteger<number_of_bits> &rhs)
	{
		return are_equal(*this, rhs);
	}

	BigInteger<number_of_bits> operator-(const BigInteger<number_of_bits> &subtrahend)
	{
		BigInteger<number_of_bits> difference;
		subtraction(this->value_in_twos_complement_representation_, subtrahend.value_in_twos_complement_representation_, difference.value_in_twos_complement_representation_);
		return difference;
	}

	BigInteger<number_of_bits> operator+(const BigInteger<number_of_bits> &rhs)
	{
		BigInteger<number_of_bits> result;
		addition(this->value_in_twos_complement_representation_, rhs.value_in_twos_complement_representation_, result.value_in_twos_complement_representation_);
		return result;
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
			has_negative_sign_ = true;
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

	std::string to_binary_string()
	{
		return value_in_twos_complement_representation_.to_string();
	}

	std::string to_number_string()
	{
		return to_decimal_string(value_in_twos_complement_representation_);
	}


private:
	inline static const auto binary_one = std::bitset<number_of_bits>(1);
	int first_bit_from_left(const std::bitset<number_of_bits> &value)
	{
		int index = value.size() - 1;
		while (index > -1 && !value.test(index))
			index--;
		return index;
	}

	void addition(std::bitset<number_of_bits> addend1, std::bitset<number_of_bits> addend2,
				  std::bitset<number_of_bits> &sum)
	{
		std::bitset<number_of_bits> carry_over;
		while (addend2.any()) {
			carry_over = (addend1 & addend2) << 1;
			addend1 ^= addend2;
			addend2 = std::move(carry_over);
		}
		sum = std::move(addend1);
	}

	void get_twos_complement(std::bitset<number_of_bits> & value)
	{
		addition(~value, binary_one, value);
	}


	void subtraction(std::bitset<number_of_bits> minuend,
					 std::bitset<number_of_bits> subtrahend,
					 std::bitset<number_of_bits> &difference)
	{
		get_twos_complement(subtrahend);
		addition(subtrahend, minuend, difference);
	}

	// We use Booth's algorithm
	void multiplication(std::bitset<number_of_bits> multiplicand, std::bitset<number_of_bits> multiplier,
						std::bitset<number_of_bits> &product)
	{


	}

	std::string to_decimal_string(std::bitset<number_of_bits> value)
	{
		constexpr int base = 10;
		std::string result{};
		if(is_negative())
		{
			get_twos_complement(value);
		}
		// Using the doubling method we iterate from left to right through the bitset. While moving right doubling
		// the digit and if bit is set, add 1.
		// Whenever we are above-equal base=10 we determine the digit by subtracting 10 and set the
		// remainder bit.
		unsigned int digit{};
		std::bitset<number_of_bits> remainder; // Temp holder of divide value
		do {
			digit = 0;
			remainder.reset();
			for (int i = value.size() - 1; i > -1; --i) {

				digit = digit * 2 + value[i];
				if (digit >= base) {
					digit -= base;
					remainder[i] = 1;
				}
			}
			value = remainder;
			result.insert(0, 1, '0' + digit);

		}
		while (value.any());

		return (is_negative() ? "-" + result : result);
	}

	bool are_equal(const BigInteger<number_of_bits> &left_hand_side, const BigInteger<number_of_bits> &right_hand_side)
	{
		if (left_hand_side.has_negative_sign_ != right_hand_side.has_negative_sign_)
			return false;
		for (int i = 0; i < number_of_bits; ++i) {
			if (right_hand_side.value_in_twos_complement_representation_[i] != left_hand_side.value_in_twos_complement_representation_[i])
				return false;
		}
		return true;
	}

	// We work with 2's complement binary representation. Leading bit is sign bit.
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
		if (has_negative_sign_)
			get_twos_complement(result);
		return result;
	}

	std::string divide_string_decimal_number_by_2(const std::string &input)
	// we divide starting from the most significant (leftmost) digit
	{
		std::string result;
		int quotient{};
		// if we divide e.g. {10, 30, 50, 70, 90,} we get {5, 15, ... } with a 5 on the following digit.
		// for {0, 20, 40, ...} this is not the case
		char zero_char = '0';
		int carry_over_five_or_zero{};
		int digit{};
		for (const auto &character: input) {
			digit = character - zero_char;
			quotient = digit / 2 + carry_over_five_or_zero;
			carry_over_five_or_zero = IS_ODD_DECIMAL_DIGIT_[digit] ? 5 : 0;
			result += zero_char + quotient;
		}
		result.erase(0, result.find_first_not_of(zero_char));
		return result;
	}

	bool has_negative_sign_{false};
	std::bitset<number_of_bits> value_in_twos_complement_representation_;
};


#endif //BIG_INTEGER_H
