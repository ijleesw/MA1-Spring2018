/*
 * To compile and link, use the following command:
 * $ g++ -O2 -std=c++11 -o groebner main.cpp -lgmp -lgmpxx
 *
 * If you want a monomial with higher degree comes before, use -DREVERSE option.
 */
#define N 2 	// # of indeterminates

#define LEADING front()
#define SMALLEST back()

#include <iostream>
#include <list>
#include <vector>
#include <gmpxx.h>
#include "polynomial.hpp"
#include "groebner.hpp"

typedef mpq_class Q;
using namespace std;

char indeterminates[N] = {'x', 'y'}; 	// array of the name of indeterminates
bool verbose = false;

/************************************************
 *
 *  Main function
 *
 ************************************************/

int main(int argc, char** argv)
{
	vector<Q> input(N);
	monomial<Q> a1, a2, b1, b2;

	if (argc < 2) {
		cout << "Input command should be";
		cout << "  "<<argv[0]<<" <case number> (optional)-v" << endl;
		return 0;
	}

	if (argc >=3 && strcmp(argv[2], "-v") == 0) verbose = true;

	switch (atoi(argv[1])) {
	case 1:
		a1.coeff = 1;
		a1.deg.push_back(3);
		a1.deg.push_back(0);

		a2.coeff = -1;
		a2.deg.push_back(1);
		a2.deg.push_back(0);


		b1.coeff = 1;
		b1.deg.push_back(2);
		b1.deg.push_back(0);

		b2.coeff = -1;
		b2.deg.push_back(0);
		b2.deg.push_back(1);

		break;

	case 2:
		a1.coeff = 1;
		a1.deg.push_back(2);
		a1.deg.push_back(2);

		a2.coeff = 1;
		a2.deg.push_back(1);
		a2.deg.push_back(1);

		b1.coeff = 1;
		b1.deg.push_back(0);
		b1.deg.push_back(4);

		b2.coeff = -1;
		b2.deg.push_back(0);
		b2.deg.push_back(2);

		break;

	default:
		cout << "Invalid case number." << endl;
		return 0;
	}

	polynomial< Q, monomial<Q> > a, b, c, d;

	a.insert(a1);
	a.insert(a2);
	cout << "a = " << a << endl;

	b.insert(b1);
	b.insert(b2);
	cout << "b = " << b << endl << endl;

	cout << "S-polynomial(a,b) = " << S_poly(a, b) << endl << endl;

	vector< polynomial< Q, monomial<Q> > > F, G;
	F.push_back(a);
	F.push_back(b);
	G = Groebner(F);

/*
	monomial<Q> a3, a4, b3, b4;

	a3.coeff = 1;
	a3.deg.push_back(1);
	a3.deg.push_back(2);

	a4.coeff = -1;
	a4.deg.push_back(0);
	a4.deg.push_back(3);

	b3.coeff = 1;
	b3.deg.push_back(0);
	b3.deg.push_back(3);

	b4.coeff = -1;
	b4.deg.push_back(0);
	b4.deg.push_back(2);

	polynomial< Q, monomial<Q> > a0, b0;
	a0.insert(a3); a0.insert(a4);
	b0.insert(b3); b0.insert(b4);
	G.push_back(a0); G.push_back(b0);

	for (auto &iter: G) cout << " " << iter << endl;
*/

	cout << "Groebner basis of F={a, b} : " << endl;
	for (auto &iter: G) cout << " " << iter << endl;
	cout << endl;

	return 0;
}