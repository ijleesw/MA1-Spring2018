#ifndef DUAL_HPP_
#define DUAL_HPP_

#include <iostream>
#include <math.h>
using namespace std;


/*****************************************************
 *
 *  Macro(s) and (commented out) function prototypes
 *
 *****************************************************/

#define X(x) dual<ring>(x)
/*
[+, -, *, /] are all overloaded
const dual<ring> exp(const dual<ring>& x);
const dual<ring> log(const dual<ring>& x);
const dual<ring> pow(const dual<ring>& x, const dual<ring>& y);
const dual<ring> sin(const dual<ring>& x);
const dual<ring> cos(const dual<ring>& x);
const dual<ring> sqrt(const dual<ring>& x);
*/


/*****************************************************
 *
 *  dual number for auto-differentiation
 *
 *****************************************************/

template <typename ring>
class dual
{
public:
	ring val;
	ring deriv;

	dual() {}
	dual(ring a) : val(a), deriv(1) {}
	dual(ring a, ring b) : val(a), deriv(b) {}
	~dual() {}

	const dual operator+(const dual& rhs) const;
	const dual operator+(const ring& rhs) const;
	const dual operator-(const dual& rhs) const;
	const dual operator-(const ring& rhs) const;
	const dual operator*(const dual& rhs) const;
	const dual operator*(const ring& rhs) const;
	const dual operator/(const dual& rhs) const;
	const dual operator/(const ring& rhs) const;

	template <typename T>
	friend ostream& operator<<(ostream&, const dual<T>&);
};


/*****************************************************
 *
 *  Operator definitions
 *
 *****************************************************/

template <typename ring>
const dual<ring> dual<ring>::operator+(const dual<ring>& rhs) const
{
	return dual<ring>(val+rhs.val, deriv+rhs.deriv);
}


template <typename ring>
const dual<ring> dual<ring>::operator+(const ring& rhs) const
{
	return dual<ring>(val+rhs, deriv);
}


template <typename ring>
const dual<ring> operator+(const ring& lhs, const dual<ring>& rhs)
{
	return dual<ring>(lhs+rhs.val, rhs.deriv);
}


template <typename ring>
const dual<ring> dual<ring>::operator-(const dual<ring>& rhs) const
{
	return dual<ring>(val-rhs.val, deriv-rhs.deriv);
}


template <typename ring>
const dual<ring> dual<ring>::operator-(const ring& rhs) const
{
	return dual<ring>(val-rhs, deriv);
}


template <typename ring>
const dual<ring> operator-(const ring& lhs, const dual<ring>& rhs)
{
	return dual<ring>(lhs-rhs.val, (-1)*rhs.deriv);
}


template <typename ring>
const dual<ring> dual<ring>::operator*(const dual<ring>& rhs) const
{
	return dual<ring>(val*rhs.val, val*rhs.deriv + deriv*rhs.val);
}


template <typename ring>
const dual<ring> dual<ring>::operator*(const ring& rhs) const
{
	return dual<ring>(val*rhs, deriv*rhs);
}


template <typename ring>
const dual<ring> operator*(const ring& lhs, const dual<ring>& rhs)
{
	return dual<ring>(lhs*rhs.val, lhs*rhs.deriv);
}


template <typename ring>
const dual<ring> dual<ring>::operator/(const dual<ring>& rhs) const
{
	if (rhs.val == 0) { cout << "Division by zero error.\n"; exit(-1); }
	return dual<ring>(val/rhs.val, (deriv*rhs.val - val*rhs.deriv) / (rhs.val*rhs.val));
}


template <typename ring>
const dual<ring> dual<ring>::operator/(const ring& rhs) const
{
	if (rhs == 0) { cout << "Division by zero error.\n"; exit(-1); }
	return dual<ring>(val/rhs, deriv/rhs);
}


template <typename ring>
const dual<ring> operator/(const ring& lhs, const dual<ring> rhs)
{
	if (rhs.val == 0) { cout << "Division by zero error.\n"; exit(-1); }
	return dual<ring>(lhs/rhs.val, (-1)*lhs*rhs.deriv / (rhs.val*rhs.val));
}


template <typename ring>
ostream& operator<<(ostream& out, const dual<ring>& x)
{
	out << x.val << "("<<x.deriv<<")";
	return out;
}


/*****************************************************
 *
 *  Additional function definitions
 *
 *****************************************************/

template <typename ring>
const dual<ring> exp(const dual<ring>& x)
{
	return dual<ring>(exp(x.val), exp(x.val)*x.deriv);
}


template <typename ring>
const dual<ring> log(const dual<ring>& x)
{
	return dual<ring>(log(x.val), (1/x.val)*x.deriv);
}


template <typename ring>
const dual<ring> pow(const dual<ring>& x, const dual<ring>& y)
{
	return exp(log(x) * y);
}


template <typename ring>
const dual<ring> sin(const dual<ring>& x)
{
	return dual<ring>(sin(x.val), cos(x.val)*x.deriv);
}


template <typename ring>
const dual<ring> cos(const dual<ring>& x)
{
	return dual<ring>(cos(x.val), (-1)*sin(x.val)*x.deriv);
}


template <typename ring>
const dual<ring> sqrt(const dual<ring>& x)
{
	return dual<ring>(sqrt(x.val), (0.5/sqrt(x.val))*x.deriv);
}


#endif  /* DUAL_HPP_ */