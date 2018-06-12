#define N 3  // # of indeterminates

#include <iostream>
#include <list>
#include <vector>
#include <gmpxx.h>
#include "polynomial.hpp"
/*
 * To compile and link, use the following command:
 * $ g++ -std=c++11 -o multivariate main.cpp -lgmp -lgmpxx
 */
typedef mpq_class Q;
using namespace std;

char indeterminates[N] = {'x', 'y', 'z'};  // name of indeterminates

int main()
{
	monomial<Q> a1, a2, a3, b1, b2;
	polynomial< Q, monomial<Q> > a, b;

	a1.coeff = "15/31";
	a1.deg = {16, 11, 13};

	a2.coeff = "-77/4";
	a2.deg = {8, 88, 76};

	a3.coeff = "12";
	a3.deg = {2, 3, 8};

	b1.coeff = "-12";
	b1.deg = {2, 3, 8};

	b2.coeff = "7749/8";
	b2.deg = {10, 15, 15};

	a.insert(a1);
	a.insert(a2);
	a.insert(a3);
	cout << "a(x, y, z) = " << a << endl;

	b.insert(b1);
	b.insert(b2);
	cout << "b(x, y, z) = " << b << endl << endl;

	cout << "a+b = " << a+b << endl;
	cout << "a-b = " << a-b << endl;
	cout << "a*b = " << a*b << endl;

	return 0;
}