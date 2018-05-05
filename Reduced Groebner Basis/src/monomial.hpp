#ifndef MONOMIAL_HPP_
#define MONOMIAL_HPP_

#include <iostream>
#include <vector>
using namespace std;

extern char indeterminates[];
extern bool verbose;

/************************************************
 *
 *  class polynomial for multivariate monomial
 *
 ************************************************/

template <typename ring>
class monomial
{
public:
	ring coeff = 0;
	vector<int> deg;

	template <typename T>
	friend ostream& operator<<(ostream&, const monomial<T>&);

	monomial();

	monomial(ring _coeff, vector<int> _deg);
	monomial(ring _coeff, ring* _deg);
	~monomial();

	int compareTo(monomial& ref);  /* for lexicographic ordering */

	int is_same(monomial& ref);
	int is_same_deg(monomial& ref);
	bool isDividedBy(monomial &ref);  /* Professor ORDERED me to use bool here! */

	int operator==(ring c);
	int operator==(monomial ref);
	int operator!=(monomial ref);

	int operator<(monomial ref);
	int operator>(monomial ref);

	monomial operator*(ring c);
	monomial operator*(monomial ref);
	monomial operator/(monomial ref);
};


/****************************************
 *
 * Function definition starts from here
 *
 ****************************************/

template <typename ring>
monomial<ring>::monomial() {}


template <typename ring>
monomial<ring>::monomial(ring _coeff, vector<int> _deg)
{
	coeff = _coeff;
	deg = _deg;
}


template <typename ring>
monomial<ring>::monomial(ring _coeff, ring* _deg)
{
	coeff = _coeff;
	copy(_deg, _deg+N, deg.begin());
}


template <typename ring>
monomial<ring>::~monomial() {}


template <typename ring>
int monomial<ring>::compareTo(monomial& ref)
{
	for (size_t i = 0; i < N; i++) {
		if (deg[i] < ref.deg[i]) return -1;
		if (deg[i] > ref.deg[i]) return 1;
	}
	return 0;
}


template <typename ring>
bool monomial<ring>::isDividedBy(monomial& ref)
{
	for (size_t i = 0; i < N; i++) {
		if (deg[i] < ref.deg[i]) return false;
	}
	return true;
}


template <typename ring>
int monomial<ring>::is_same_deg(monomial& ref)
{
	return compareTo(ref) == 0;
}


template <typename ring>
int monomial<ring>::is_same(monomial& ref)
{
	return (compareTo(ref) == 0 && coeff == ref.coeff);		
}


template <typename ring>
int monomial<ring>::operator==(ring c)
{
	if (coeff != c) return 0;
	for (auto &iter: deg) {
		if (iter != 0) return 0;
	}
	return 1;
}


template <typename ring>
int monomial<ring>::operator==(monomial ref)
{
	return is_same(ref);
}


template <typename ring>
int monomial<ring>::operator!=(monomial ref)
{
	return !is_same(ref);
}


template <typename ring>
int monomial<ring>::operator<(monomial ref)
{
	return (compareTo(ref) < 0);
}


template <typename ring>
int monomial<ring>::operator>(monomial ref)
{
	return (compareTo(ref) > 0);
}


template <typename ring>
monomial<ring> monomial<ring>::operator*(ring c)
{
	monomial res(coeff*c, deg);
	return res;
}


template <typename ring>
monomial<ring> monomial<ring>::operator*(monomial ref)
{
	ring mult_coeff = 1;
	vector<int> mult_deg;

	mult_coeff *= (coeff * ref.coeff);
	for (size_t i = 0; i < N; i++) mult_deg.push_back(deg[i] + ref.deg[i]);
	
	monomial res(mult_coeff, mult_deg);
	return res;
}


template <typename ring>
monomial<ring> monomial<ring>::operator/(monomial ref)
{
	int can_divide = 1;
	ring div_coeff = coeff;
	vector<int> div_deg;

	div_coeff /= ref.coeff;
	for (size_t i = 0; i < N; i++) {
		div_deg.push_back(deg[i] - ref.deg[i]);
		if (deg[i] < ref.deg[i]) can_divide = 0;
	}
	if (!can_divide) {
		div_coeff = 0;
		div_deg.resize(N, 0);
	}
	monomial res(div_coeff, div_deg);
	return res;
}


template <typename ring>
ostream& operator<<(ostream& out, const monomial<ring>& m)
{
	out << m.coeff << " ";
	for (size_t i = 0; i < N; i++) {
		if (m.deg[i] != 0) out << indeterminates[i] << "^" << m.deg[i] << " ";
	}
	return out;
}

#endif