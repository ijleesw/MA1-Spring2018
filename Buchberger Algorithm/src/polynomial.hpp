#ifndef POLYNOMIAL_HPP_
#define POLYNOMIAL_HPP_

#define LEADING front()
#define SMALLEST back()

#include <iostream>
#include <list>
#include <vector>
#include "monomial.hpp"
using namespace std;

/************************************************
 *
 *  class polynomial for multivariate polynomial
 *
 ************************************************/

template <typename ring, class monomial>
class polynomial
{
public:
	list<monomial> terms;

	polynomial();
	polynomial(monomial ref);
	~polynomial();

	template <typename T1, class T2>
	friend ostream& operator<<(ostream&, const polynomial<T1, T2>&);

	void insert(monomial mono);
	void neg_insert(monomial mono);

	void clear(void);

	int is_zero();
	int is_same(polynomial& ref);
	int is_same_leading_deg(polynomial& ref);
	int isDividedBy(polynomial& ref);

	void divideby(polynomial& d, polynomial& q, polynomial& r);  /* Given d, (*this) = dq + r */

	int operator==(polynomial& ref);
	int operator!=(polynomial& ref);

	polynomial operator+(polynomial& ref);
	polynomial operator-(polynomial& ref);
	polynomial operator*(polynomial& ref);
	polynomial operator/(monomial& ref);  /* naive division only allowed for monomials */
	polynomial operator%(polynomial& ref);

	polynomial bar_(vector< polynomial >& G);  /* division of (*this) by a set G */
};

template <typename ring, class monomial>
static inline monomial LT(polynomial<ring, monomial>& f);

template <typename ring, class monomial>
static inline ring LC(polynomial<ring, monomial>& f);

template <typename ring, class monomial>
monomial LM(polynomial<ring, monomial>& f);


/****************************************
 *
 *  Function definitions start here
 *
 ****************************************/

template <typename ring, class monomial>
polynomial<ring, monomial>::polynomial() {}


template <typename ring, class monomial>
polynomial<ring, monomial>::polynomial(monomial ref)
{
	terms.push_back(ref);
}


template <typename ring, class monomial>
polynomial<ring, monomial>::~polynomial() {}


template <typename ring, class monomial>
void polynomial<ring, monomial>::insert(monomial mono)
{
	if (mono.coeff == 0) return;  /* ignore monomials with zero coeff */

	typename list<monomial>::iterator iter;
	for (iter = terms.begin(); iter != terms.end(); iter++) {
		if ((*iter).is_same_deg(mono))  /* Case 1. : just add coeff */
		{
			iter->coeff += mono.coeff;
			if (iter->coeff == 0) {  /* if coeff is zero, then erase the term */
				terms.erase(iter);
			}
			return;
		}
		else if (mono > *iter)  /* Case 2. : add mono as a new element in terms */
		{
			terms.insert(iter, mono);
			return;
		}
	}
	/* if reached here, then mono not inserted yet */
	terms.push_back(mono);
	return;
}


template <typename ring, class monomial>
void polynomial<ring, monomial>::neg_insert(monomial mono)
{
	mono.coeff *= -1;
	insert(mono);
}


template <typename ring, class monomial>
void polynomial<ring, monomial>::clear(void)
{
	terms.clear();
}


template <typename ring, class monomial>
int polynomial<ring, monomial>::is_zero()
{
	return terms.empty();
}


template <typename ring, class monomial>
int polynomial<ring, monomial>::is_same(polynomial& ref)
{
	int terms_size = terms.size();
	if (terms_size != ref.terms.size()) return 0;
	if (this->is_zero()) return 1;

	auto this_iter = terms.begin();
	auto ref_iter = ref.terms.begin();
	for (size_t i = 0; i < terms_size; i++) {
		if (*this_iter != *ref_iter) return 0;
		advance(this_iter, 1);
		advance(ref_iter, 1);
	}
	return 1;
}


template <typename ring, class monomial>
int polynomial<ring, monomial>::is_same_leading_deg(polynomial& ref)
{
	return terms.LEADING.is_same_deg(ref.terms.LEADING);
}


template <typename ring, class monomial>
int polynomial<ring, monomial>::isDividedBy(polynomial& ref)
{
	return terms.LEADING.isDividedBy(ref.terms.LEADING);
}	


template <typename ring, class monomial>
void polynomial<ring, monomial>::divideby(polynomial& d, polynomial& q, polynomial& r)
{
	q.clear();
	r = (*this);

	monomial r_leading = r.terms.LEADING;
	monomial d_leading = d.terms.LEADING;

	polynomial multiplier, tmp;
	monomial mono_mult;

	while (r.isDividedBy(d)) {
		multiplier.clear();

		mono_mult = r_leading/d_leading;
		if (mono_mult.coeff == 0) break;
		multiplier.insert(mono_mult);
		q.insert(mono_mult);

		tmp = d * multiplier;
		r = r - tmp;
		if (r.is_zero()) break;
		r_leading = r.terms.LEADING;
	}
}


template <typename ring, class monomial>
int polynomial<ring, monomial>::operator==(polynomial& ref)
{
	return is_same(ref);
}


template <typename ring, class monomial>
int polynomial<ring, monomial>::operator!=(polynomial& ref)
{
	return !is_same(ref);
}


template <typename ring, class monomial>
polynomial<ring, monomial> polynomial<ring, monomial>::operator+(polynomial& ref)
{
	polynomial res;
	for (auto &iter: terms) res.insert(iter);
	for (auto &iter: ref.terms) res.insert(iter);
	return res;
}


template <typename ring, class monomial>
polynomial<ring, monomial> polynomial<ring, monomial>::operator-(polynomial& ref)
{
	polynomial res;
	for (auto &iter: terms) res.insert(iter);
	for (auto &iter: ref.terms) res.neg_insert(iter);
	return res;
}


template <typename ring, class monomial>
polynomial<ring, monomial> polynomial<ring, monomial>::operator*(polynomial& ref)
{
	polynomial res;
	for (auto &iter_lhs: terms) {
		for (auto &iter_rhs: ref.terms) {
			res.insert(iter_lhs * iter_rhs);
		}
	}
	return res;
}


template <typename ring, class monomial>
polynomial<ring, monomial> polynomial<ring, monomial>::operator/(monomial& ref)
{
	polynomial res;
	for (auto &iter_lhs: terms) {
		res.insert(iter_lhs / ref);
	}
	return res;
}


template <typename ring, class monomial>
polynomial<ring, monomial> polynomial<ring, monomial>::operator%(polynomial& ref)
{
	polynomial q, r;
	divideby(ref, q, r);
	return r;
}


template <typename ring, class monomial>
static inline monomial LT(polynomial<ring, monomial>& f)
{
	return f.terms.LEADING;
}


template <typename ring, class monomial>
static inline ring LC(polynomial<ring, monomial>& f)
{
	return f.terms.LEADING.coeff;
}


template <typename ring, class monomial>
monomial LM(polynomial<ring, monomial>& f)
{
	monomial res = f.terms.LEADING;
	res.coeff = 1;
	return res;
}


template <typename ring, class monomial>
polynomial<ring, monomial> polynomial<ring, monomial>::bar_(vector< polynomial >& G)
{
	int s = G.size();

	polynomial f = (*this);
	polynomial r, EMPTY;
	polynomial tmp_q, tmp_r, tmp;

	int terminate_flag=0;
	while (f != EMPTY && !(terminate_flag++)) {
		for (size_t i = 0; i < s; i++) {
			polynomial LT_f(LT(f)), LT_Gi(LT(G[i]));
			tmp_q.clear(); tmp_r.clear(); tmp.clear();
			LT_f.divideby(LT_Gi, tmp_q, tmp_r);

			if (tmp_r == EMPTY) {
				Q[i] = Q[i] + tmp_q;
				tmp = tmp_q * G[i];
				f = f - tmp;
				r = r + LT_f;
				terminate_flag = 0;
				break;
			}
		}
	}
	return f;
}


template <typename ring, class monomial>
ostream& operator<<(ostream& out, const polynomial< ring, monomial >& m)
{
	int cnt = 0;
	if (m.terms.empty()) { out << "0"; return out; }
#ifndef REVERSE
	for (auto &iter: m.terms) {
		if (cnt >= 1) out << " + ";
		out << "( " << iter << ")";
		cnt++;
	}
#else
	for (auto iter = m.terms.rbegin(); iter != m.terms.rend(); iter++) {
		if (cnt >= 1) out << " + ";
		out << "( " << *iter << ")";
		cnt++;
	}
#endif
	return out;
}

#endif  /* POLYNOMIAL_HPP_ */