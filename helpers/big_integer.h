//
// Created by andreas on 02.09.22.
//

#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <bitset>
#include <utility>
#include <algorithm>
#include <iostream>
#include <array>

constexpr static std::array<int, 10> IS_ODD_DECIMAL_DIGIT_ = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1};

// We work with 2's complement binary representation
template<size_t number_of_bits>
class BigInteger {
public:

    explicit BigInteger() {
        std::bitset<number_of_bits>();
    }

    explicit BigInteger(const long long &initial_value) {
        value_in_twos_complement_representation_ = std::bitset<number_of_bits>(initial_value);
    }

    explicit BigInteger(const std::string &value) {
        value_in_twos_complement_representation_ = _convert_string_to_bitset(value);
    }

    explicit BigInteger(const std::bitset<number_of_bits> &initial_value)
            :
            value_in_twos_complement_representation_(initial_value) {

    }

    // Copy constructor
    BigInteger(const BigInteger<number_of_bits> &other)
            :
            value_in_twos_complement_representation_(other.value_in_twos_complement_representation_) {
    }

    // Assignment operators
    BigInteger &operator=(const BigInteger<number_of_bits> &other) {
        value_in_twos_complement_representation_ = other.value_in_twos_complement_representation_;
        return *this;

    }

    bool is_negative() const {
        return value_in_twos_complement_representation_[number_of_bits - 1];
    }

    // Equal operator
    bool operator==(const BigInteger<number_of_bits> &rhs) {
        return _are_equal(*this, rhs);
    }

    // Unequal operator
    bool operator!=(const BigInteger<number_of_bits> &rhs) {
        return !_are_equal(*this, rhs);
    }

    BigInteger<number_of_bits> operator-(const BigInteger<number_of_bits> &subtrahend) {
        BigInteger<number_of_bits> difference;
        _subtraction(this->value_in_twos_complement_representation_,
                     subtrahend.value_in_twos_complement_representation_,
                     difference.value_in_twos_complement_representation_);
        return difference;
    }


    // unary minus sign operator
    BigInteger<number_of_bits> operator-() {
        _get_twos_complement(this->value_in_twos_complement_representation_);
        return *this;
    }

    BigInteger<number_of_bits> operator+(const BigInteger<number_of_bits> &addend) {
        BigInteger<number_of_bits> sum;
        _addition(this->value_in_twos_complement_representation_,
                  addend.value_in_twos_complement_representation_,
                  sum.value_in_twos_complement_representation_);
        return sum;
    }

    BigInteger<number_of_bits> & operator+=(const BigInteger<number_of_bits> &addend) {
        _addition(this->value_in_twos_complement_representation_,
                  addend.value_in_twos_complement_representation_,
                  this->value_in_twos_complement_representation_);
        return *this;
    }

    BigInteger<number_of_bits> operator*(const BigInteger<number_of_bits> &rhs) {
        BigInteger<number_of_bits> result;
        bool is_negative = this->is_negative() ^ rhs.is_negative();
        auto multiplicand = this->value_in_twos_complement_representation_;
        auto multiplier = rhs.value_in_twos_complement_representation_;

        if (this->is_negative())
            _get_twos_complement(multiplicand);
        if (rhs.is_negative())
            _get_twos_complement(multiplier);

        _multiplication(multiplicand, multiplier, result.value_in_twos_complement_representation_);
        if (is_negative)
            _get_twos_complement(result.value_in_twos_complement_representation_);
        return result;
    }

    BigInteger<number_of_bits> &operator*=(const BigInteger<number_of_bits> &rhs) {
        bool is_negative = this->is_negative() ^ rhs.is_negative();
        auto multiplicand = this->value_in_twos_complement_representation_;
        auto multiplier = rhs.value_in_twos_complement_representation_;

        if (this->is_negative())
            _get_twos_complement(multiplicand);
        if (rhs.is_negative())
            _get_twos_complement(multiplier);

        _multiplication(multiplicand, multiplier, this->value_in_twos_complement_representation_);
        if (is_negative)
            _get_twos_complement(this->value_in_twos_complement_representation_);

        return *this;
    }

    std::string validate_string_and_determine_sign(const std::string &str, bool &is_negative) {
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
            is_negative = true;
            first_digit_position = 1;
        }
        if (str[first_digit_position] == '0') {
            throw std::invalid_argument("BigInteger: Leading zero in string detected: " + str);
        }
        if (!std::all_of(str.cbegin() + first_digit_position, str.cend(), [](char c) { return std::isdigit(c); })) {
            throw std::invalid_argument("BigInteger: String contains non-numeric values: " + str);
        }
        return str.substr(first_digit_position);
    }

    std::string to_binary_string() {
        return value_in_twos_complement_representation_.to_string();
    }

    std::string to_number_string() {
        return _to_decimal_string(value_in_twos_complement_representation_);
    }

    BigInteger<number_of_bits> to_power(int64_t exponent) {
        auto base = *this;
        auto help = BigInteger<number_of_bits>(1);
        while (exponent > 1) {
            if (exponent & 1) {
                help *= base;
                exponent--;
            }
            exponent >>= 1;
            base *= base;
        }
        return base*help;

    }

private:
    inline static const auto binary_one = std::bitset<number_of_bits>(1);

    int _first_bit_from_left(const std::bitset<number_of_bits> &value) {
        int index = value.size() - 1;
        while (index > -1 && !value.test(index))
            index--;
        return index;
    }

    void _addition(std::bitset<number_of_bits> addend1, std::bitset<number_of_bits> addend2,
                   std::bitset<number_of_bits> &sum) {
        std::bitset<number_of_bits> carry_over;
        while (addend2.any()) {
            carry_over = (addend1 & addend2) << 1;
            addend1 ^= addend2;
            addend2 = std::move(carry_over);
        }
        sum = std::move(addend1);
    }

    void _get_twos_complement(std::bitset<number_of_bits> &value) {
        _addition(~value, binary_one, value);
    }

    void _subtraction(std::bitset<number_of_bits> minuend,
                      std::bitset<number_of_bits> subtrahend,
                      std::bitset<number_of_bits> &difference) {
        _get_twos_complement(subtrahend);
        _addition(minuend, subtrahend, difference);
    }

    bool _enough_bits_for_product(int left_bit_multiplicand, int left_bit_multiplier) {
        return number_of_bits >= left_bit_multiplicand + left_bit_multiplier;
    }

    // We use Booth's algorithm
    void _multiplication(std::bitset<number_of_bits> multiplicand, std::bitset<number_of_bits> multiplier,
                         std::bitset<number_of_bits> &result) {
        if (!_enough_bits_for_product(_first_bit_from_left(multiplicand), _first_bit_from_left(multiplier)))
            throw std::out_of_range(
                    "Number of bits " + std::to_string(number_of_bits) + " is not enough to hold product!");

        bool last_cycle_bit{false};
        std::bitset<number_of_bits> product;
        bool most_significand_bit{false};
        for (int index = 0; index < number_of_bits; ++index) {
            if (multiplier[0] && !last_cycle_bit)
                _subtraction(product, multiplicand, product);
            else if (!multiplier[0] && last_cycle_bit)
                _addition(product, multiplicand, product);
            most_significand_bit = product[number_of_bits - 1];
            last_cycle_bit = multiplier[0];

            multiplier >>= 1;
            multiplier[number_of_bits - 1] = product[0];
            product >>= 1;
            product[number_of_bits - 1] = most_significand_bit;

        }
        product = multiplier;
        result = product;
    }

    std::string _to_decimal_string(std::bitset<number_of_bits> value) {
        constexpr int base = 10;
        std::string result{};
        if (is_negative()) {
            _get_twos_complement(value);
        }
        // Using the doubling method we iterate from left to right through the bitset. While moving right, doubling
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

        } while (value.any());

        return (is_negative() ? "-" + result : result);
    }

    bool
    _are_equal(const BigInteger<number_of_bits> &left_hand_side, const BigInteger<number_of_bits> &right_hand_side) {
        for (int i = number_of_bits - 1; i > -1; --i) {
            if (right_hand_side.value_in_twos_complement_representation_[i]
                != left_hand_side.value_in_twos_complement_representation_[i])
                return false;
        }
        return true;
    }

    // We work with 2's complement binary representation. Leading bit is sign bit.
    std::bitset<number_of_bits> _convert_string_to_bitset(const std::string &str) {
        bool is_negative{};
        auto absolute_value_string = validate_string_and_determine_sign(str, is_negative);
        int digit{};
        int bit_index{};
        std::bitset<number_of_bits> result;
        while (!absolute_value_string.empty()) {
            digit = absolute_value_string.back() - '0';
            // instead of 'modulo 2' operation we just set the bits for odd decimal digits
            result[bit_index++] = IS_ODD_DECIMAL_DIGIT_[digit];
            absolute_value_string = _divide_string_decimal_number_by_2(absolute_value_string);
        }
        if (is_negative)
            _get_twos_complement(result);
        return result;
    }

    std::string _divide_string_decimal_number_by_2(const std::string &input)
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

    std::bitset<number_of_bits> value_in_twos_complement_representation_;
};


#endif //BIG_INTEGER_H
