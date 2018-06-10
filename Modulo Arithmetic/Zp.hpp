#ifndef ZP_HPP_
#define ZP_HPP_

#define P 17

#include <iostream>
using namespace std;

class Zp {
public:
	int val;  // it is guaranteed that 0 <= val < p

	Zp() { val = 0; }
	Zp(int _val) { val = (_val % P + P) % P; };
	Zp& operator=(const int&);

	const Zp operator+(const Zp&) const;
	const Zp operator-(const Zp&) const;
	const Zp operator*(const Zp&) const;
	const Zp operator/(const Zp&) const;

	const int operator==(const Zp&) const;
	const int operator==(const int&) const;
	const int operator!=(const Zp&) const;
	const int operator!=(const int&) const;

	friend ostream& operator<<(ostream&, const Zp&);
};

Zp& Zp::operator=(const int& rhs)
{
	val = (rhs % P + P) % P;
	return *this;
}

const int pow(const int& a, const int& e)
{
	if (e == 0) return 1;
	if (e & 1) return (pow(a, e-1) * a % P);
	int tmp = pow(a, e/2);
	return tmp * tmp;
}

const Zp Zp::operator+(const Zp& rhs) const
{
	return Zp(val+rhs.val);
}

const Zp Zp::operator-(const Zp& rhs) const
{
	return Zp(val-rhs.val);
}

const Zp Zp::operator*(const Zp& rhs) const
{
	return Zp(val*rhs.val);
}

const Zp Zp::operator/(const Zp& rhs) const
{
	assert (rhs != 0);

	int rhs_inv = pow((rhs.val % P + P) % P, P-2) % P;
	assert (rhs_inv != 0);

	return Zp(val*rhs_inv);
}

const int Zp::operator==(const Zp& rhs) const
{
	return (val == rhs.val);
}

const int Zp::operator==(const int& rhs) const
{
	return (val == (rhs % P + P) % P);
}

const int Zp::operator!=(const Zp& rhs) const
{
	return (val != rhs.val);
}

const int Zp::operator!=(const int& rhs) const
{
	return (val != (rhs % P + P) % P);
}

ostream& operator<<(ostream& out, const Zp& a)
{
	out << a.val;
	return out;
}

#endif /* ZP_HPP_ */