
#include <bitset>//for bitset
#include <cstddef>//for size_t
#include <algorithm>//for min
#include <stdexcept>
#include <iostream>

const std::size_t BIT8 = 8u;

const std::size_t BIT16 = 16u;

const std::size_t BIT32 = 10u;

const std::size_t BIT64 = 64u;

class cpu_model
{
	typedef std::bitset<BIT8> resister8;
	typedef std::bitset<BIT16> register16;
	typedef std::bitset<BIT32> register32;
	typedef std::bitset<BIT64> register64;
public:
	cpu_model();
	cpu_model(const cpu_model &) = delete;
	cpu_model &operator=(const cpu_model &) = delete;
	~ cpu_model() = default;
public:
	void clear();
	const register32 &plus(const register32 &, const register32 &);
	const register32 &sub(const register32 &, const register32 &);
	const register64 &mult(const register32 &, const register32 &);
	const register32 &div(const register32 &, const register32 &);
private:
	const register32 negative(const register32 &);
private:
	bool m_flag;
	register32 m_lhs;
	register32 m_rhs;
	register32 m_ax;
	register32 multiplier;
	register32 m_tmp;
	register64 m_mult;
};

cpu_model::cpu_model()
	: m_flag(false)
{
}

void cpu_model::clear()
{
	m_lhs.reset();
	m_rhs.reset();
	m_ax.reset();
	m_flag = false;
	multiplier.reset();
	m_tmp.reset();
}

const std::bitset<BIT32> &cpu_model::plus(const register32 &lhs, const register32 &rhs)
{
	m_lhs = lhs;
	m_rhs = rhs;
	bool flag = false;//In order to carry
	std::size_t index = 0u;
	for (std::size_t i = 0u; i != m_rhs.size(); ++i) {
		if (m_lhs[i] && m_rhs[i]) {//If the same and is 1, then you need to carry
			if (!flag) m_lhs[i] = ~m_lhs[i];
			flag = true;//The flag is set to 1
			flag = true;//The flag is set to 1
		}
		else {
			m_lhs[i] = m_lhs[i] ^ m_rhs[i];
			if (flag) m_lhs[i] = ~m_lhs[i];
			if (m_lhs[i])
				flag =
					false;//When it is 0, it is negated to 1, at this time it is not necessary to carry out the subsequent operations.
		}
	}
	return m_lhs;
}

const std::bitset<BIT32> &cpu_model::sub(const register32 &lhs, const register32 &rhs)
{
	register32 tmp = negative(rhs);//reverse first
	return plus(lhs, tmp);//Add 1 to get the opposite number
}

const std::bitset<BIT32> cpu_model::negative(const register32 &item)
{
	register32 res(item);
	res.flip();
	return plus(res, register32(1));
}

const std::bitset<BIT64> &cpu_model::mult(const register32 &multiplicand, const register32 &rhs)
{
	this->clear();
	multiplier = rhs;
	bool back;
	for (std::size_t i = 0; i != rhs.size(); ++i) {
		if (multiplier[0] && !m_flag) {
			m_ax = sub(m_ax, multiplicand);
		}
		else if (!multiplier[0] && m_flag) {
			m_ax = plus(m_ax, multiplicand);
		}
		std::cout << "Multiplier1 " << i<< " ";
		for(int i=0; i < 10; ++i)
			std::cout << multiplier[i];
		std::cout << std::endl;

		back = m_ax[BIT32 - 1];
		//shift
		m_flag = multiplier[0];

		multiplier >>= 1;
		multiplier[BIT32 - 1] = m_ax[0];
		m_ax >>= 1;
		m_ax[BIT32 - 1] = back;
		std::cout << "Multiplier" << i<< " ";
		for(int i=0; i < 10; ++i)
			std::cout << multiplier[i];
		std::cout << std::endl;

	}
	std::cout<< " Ulong " << m_ax.to_ulong() << std::endl;
	std::cout << " Ulong2 " << multiplier.to_ulong() << std::endl;
	m_mult = m_ax.to_ulong();
	register64 tmp = multiplier.to_ulong();
	m_mult <<= BIT32;
	m_mult |= tmp;
	return m_mult;
}

const std::bitset<BIT32> &cpu_model::div(const register32 &lhs, const register32 &rhs)
{
	if (!rhs.to_ulong()) throw std::invalid_argument("");
	if (lhs.to_ulong() < rhs.to_ulong()) return (m_ax = 0);
	clear();
	multiplier = lhs;
	m_rhs = negative(rhs);
	for (std::size_t i = 0; i!= rhs.size(); ++i) {
		m_ax <<= 1;
		m_ax[0] = multiplier[BIT32 - 1];
		multiplier <<= 1;
		m_tmp = plus(m_ax, m_rhs);
		multiplier[0] = ~m_tmp[BIT32 - 1];
		if (multiplier[0]) m_ax = m_tmp;
	}
	return multiplier;
}

int main(int argc, char *argv[])
{
	cpu_model test;
	int j = 3;
	std::cout << test.mult(std::bitset<10>(9), std::bitset<10>(17));
//	std::cout << test.plus(std::bitset<32>(7), std::bitset<32>(13));
//std :: cout << test.sub (std :: bitset <32> (0), std :: bitset <32> (2));
	return 0;
}