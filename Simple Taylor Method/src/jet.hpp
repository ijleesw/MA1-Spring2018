#ifndef JET_HPP_
#define JET_HPP_

#include "vector_tools.hpp"
using namespace std;


/*****************************************************
 *
 *  Jet for simple Taylor method & Macro
 *
 *****************************************************/

#define JET_INIT(len) Jet<R>(len, vector<R>(len, 0))


template <typename R>
class Jet
{
public:
	vector<R> elt;

	Jet(int length) {
		elt.reserve(length);
		fill(elt.begin(), elt.end(), 0);
	}
	Jet(int length, R a) {
		elt.reserve(length);
		elt[0] = a;
	}
	Jet(int length, vector<R> init_elt) {
		elt.reserve(length);
		copy(init_elt.begin(), init_elt.end(), back_inserter(elt));
	}
	~Jet() {}

	void init(void);

	R& at(const int&);
	const int length(void) const;

	const R eval(const R&) const;
	
	const Jet operator+(const Jet&) const;
	const Jet operator-(const Jet&) const;
	const Jet operator*(const Jet&) const;
	const Jet operator*(const R&) const;

	template <typename T>
	friend ostream& operator<<(ostream&, const Jet<T>&);
};


/*****************************************************
 *
 *  Member function definitions
 *
 *****************************************************/

template <typename R>
void Jet<R>::init(void)
{
	fill(elt.begin(), elt.end(), 0);
}


template <typename R>
R& Jet<R>::at(const int& i)
{
	assert(i >= 0 && i < elt.size());
	return elt[i];
}


template <typename R>
const int Jet<R>::length(void) const
{
	return elt.size();
}


template <typename R>
const R Jet<R>::eval(const R& x) const
{
	int size = elt.size();
	R res = elt[0];
	R e = x;
	for (int i = 1; i < size; i++) {
		res += elt[i]*e;
		e *= x;
	}
	return res;
}


template <typename R>
const Jet<R> Jet<R>::operator+(const Jet<R>& rhs) const
{
	int max_size = max(elt.size(), rhs.elt.size());
	return Jet<R>(max_size, (this->elt)+(rhs.elt));
}


template <typename R>
const Jet<R> Jet<R>::operator-(const Jet<R>& rhs) const
{
	int max_size = max(elt.size(), rhs.elt.size());
	return Jet<R>(max_size, (this->elt)-(rhs.elt));
}


template <typename R>
const Jet<R> Jet<R>::operator*(const Jet<R>& rhs) const
{
	int lhs_size = elt.size();
	int rhs_size = rhs.elt.size();
	int max_size = max(lhs_size, rhs_size);

	vector<R> res(max_size);
	for (int i = 0; i < lhs_size; i++) {
		int tmp_size = min(rhs_size, max_size-i);
		for (int j = 0; j < tmp_size; j++) {
			res[i+j] += elt[i] * rhs.elt[j];
		}
	}
	return Jet<R>(max_size, res);
}


template <typename R>
const Jet<R> Jet<R>::operator*(const R& rhs) const
{
	return Jet<R>(elt.size(), (this->elt)*rhs);
}


template <typename R>
ostream& operator<<(ostream& out, const Jet<R>& j)
{
	int size = j.elt.size();
	out << "["<<j.elt[0];
	if (size > 1) out << " + "<<j.elt[1]<<"ε";
	for (int i = 2; i < size; i++) {
		out << " + "<<j.elt[i]<<"ε^"<<i;
	}
	out << "]";
	return out;
}


#endif /* JET_HPP_ */