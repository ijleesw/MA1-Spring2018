#ifndef BUCHBERGER_HPP_
#define BUCHBERGER_HPP_

#include <iostream>
#include <vector>
#include "polynomial.hpp"
using namespace std;

extern bool verbose;

/************************************************
 *
 *  Function declarations for Buchberger Algo.
 *
 ************************************************/

template <typename ring, class monomial>  /* it returns LCM of leading terms */
monomial LCM(polynomial< ring, monomial >& f, polynomial< ring, monomial >& g);

template <typename ring, class monomial>
polynomial< ring, monomial> S_poly(polynomial< ring, monomial >& f, polynomial< ring, monomial >& g);

template <typename ring, class monomial>
void term_reduction(polynomial< ring, monomial >& f, polynomial< ring, monomial >& g);

template <typename ring, class monomial>
void basis_normalization(vector< polynomial< ring, monomial > >& B);

template <typename ring, class monomial>
void basis_dropout(vector< polynomial< ring, monomial > >& B);

template <typename ring, class monomial>
void basis_reduction(vector< polynomial< ring, monomial > >& B);

template <typename ring, class monomial>
vector< polynomial< ring, monomial > > Buchberger(vector< polynomial< ring, monomial > >& F);


/************************************************
 *
 *  Function definitions start here
 *
 ************************************************/

template <typename ring, class monomial>  /* it returns LCM of leading terms */
monomial LCM(polynomial< ring, monomial >& f, polynomial< ring, monomial >& g)
{
	vector<int> deg;
	for (size_t i = 0; i < N; i++) {
		f.terms.LEADING.deg[i] > g.terms.LEADING.deg[i] ?
			deg.push_back(f.terms.LEADING.deg[i]) : deg.push_back(g.terms.LEADING.deg[i]);
	}
	monomial lcm(1, deg);
	return lcm;
}


template <typename ring, class monomial>
polynomial< ring, monomial> S_poly(polynomial< ring, monomial >& f, polynomial< ring, monomial >& g)
{
	polynomial< ring, monomial > S, s, t, tmp1, tmp2;
	polynomial< ring, monomial > l(LCM(f, g));
	s.insert(l.terms.LEADING/f.terms.LEADING);
	t.insert(l.terms.LEADING/g.terms.LEADING);
	tmp1 = s*f;
	tmp2 = t*g;
	S = tmp1 - tmp2;
	return S;
}


template <typename ring, class monomial>
void term_reduction(polynomial< ring, monomial >& f, polynomial< ring, monomial >& g)
{
	monomial g_leading = LT(g);
	size_t f_length;
	int is_reduced;

	do {
		is_reduced = 0;
		f_length = f.terms.size();
		for (auto &iter_f: f.terms) {
			if (iter_f.isDividedBy(g_leading)) {
				monomial mono_mult = iter_f/g_leading;
				polynomial<ring, monomial> multiplier(mono_mult), tmp;
				tmp = g * multiplier;
				f = f - tmp;
				is_reduced=1;
				break;
			}
		}
	} while (is_reduced);
}


template <typename ring, class monomial>
void basis_normalization(vector< polynomial< ring, monomial > >& B)
{
	for (auto &B_elt: B) {
		ring lc = LC(B_elt);
		for (auto &iter_terms: B_elt.terms) {
			iter_terms.coeff /= lc;
		}
	}
}


template <typename ring, class monomial>
void basis_dropout(vector< polynomial< ring, monomial > >& B)
{
	vector<monomial> tmp;
	size_t B_size = B.size();
	auto B_begin = B.begin();
	int* will_be_dropped = (int*)calloc(B_size, sizeof(int));

	for (auto &iter_B: B) tmp.push_back(LT(iter_B));

	for (size_t i = 0; i < B_size; i++) {
		for (size_t j = i+1; j < B_size; j++) {
			if (tmp[i].isDividedBy(tmp[j])) {
				will_be_dropped[i] = 1;
				continue;
			}
			else if (tmp[j].isDividedBy(tmp[i])) {
				will_be_dropped[j] = 1;
				continue;
			}
		}
	}

	size_t i = B_size;
	while (i--) {
		if (will_be_dropped[i]) B.erase(B_begin+i);
	}
	free(will_be_dropped);
}


template <typename ring, class monomial>
void basis_reduction(vector< polynomial< ring, monomial > >& B)
{
	basis_normalization(B);
	basis_dropout(B);  /* now B is a minimal Groebner basis */
	
	size_t B_size = B.size();
	for (size_t i = 0; i < B_size; i++) {
		for (size_t j = 0; j < B_size; j++) {
			if (i == j) continue;
			term_reduction(B[i], B[j]);
		}
	}
}


template <typename ring, class monomial>
vector< polynomial< ring, monomial > > Buchberger(vector< polynomial< ring, monomial > >& F)
{
	polynomial< ring, monomial > EMPTY;
	vector< polynomial< ring, monomial > > G = F;
	int epoch=0;
	int curr_G_size;

	do {
		if (verbose)
			cout << "Epoch : " << ++epoch << endl;
		curr_G_size = G.size();
		int sub_epoch = 0;
		for (size_t i = 0; i < curr_G_size-1; i++) {
			if (verbose)
				cout << "  Sub Epoch : " << ++sub_epoch << endl;
			for (size_t j = i+1; j < curr_G_size; j++) {
				int s_exists = 0;

				polynomial< ring, monomial > s = S_poly(G[i], G[j]);
				if (s == EMPTY) continue;

				polynomial< ring, monomial > r = s.bar_(G);
				if (r == EMPTY) continue;
				if (!s_exists) G.push_back(r);
			}
		}
	} while (G.size() != curr_G_size);
	
	basis_reduction(G);
	return G;
}

#endif  /* BUCHBERGER_HPP_ */