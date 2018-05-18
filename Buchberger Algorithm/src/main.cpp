/*
 * Buchberger Algorithm for computing Reduced Groebner Basis
 *
 * @ijleesw
 */
#define N 5 	// maximum # of indeterminates

#include <iostream>
#include <gmpxx.h>
#include "polynomial.hpp"
#include "buchberger.hpp"

typedef mpq_class Q;
using namespace std;
bool verbose = false;

char indeterminates[N]; 	// array of the name of indeterminates

/************************************************
 *
 *  Main function
 *
 ************************************************/

int main(int argc, char** argv)
{
	monomial<Q> a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, d1, d2, e1, e2;
	polynomial< Q, monomial<Q> > a, b, c, d, e, EMPTY;
	vector< polynomial< Q, monomial<Q> > > F, G;

	if (argc < 2) {
		cout << "Usage: "<<argv[0]<<" <case number> (optional)-v" << endl;
		return 0;
	}

	if (argc >=3 && strcmp(argv[2], "-v") == 0) verbose = true;

	switch (atoi(argv[1])) {
	case 1:
		indeterminates[0] = 'x';
		indeterminates[1] = 'y';
		indeterminates[2] = 'z';

		a1.coeff = 1;
		a1.deg = {2,0,0,0,0};

		a2.coeff = 1;
		a2.deg = {0,2,0,0,0};

		a3.coeff = 1;
		a3.deg = {0,0,2,0,0};

		a4.coeff = -1;
		a4.deg = {0,0,0,0,0};

		a.insert(a1); a.insert(a2); a.insert(a3); a.insert(a4);

		b1.coeff = 1;
		b1.deg = {3,0,0,0,0};

		b2.coeff = 1;
		b2.deg = {2,0,0,0,0};

		b3.coeff = -1;
		b3.deg = {0,2,0,0,0};

		b4.coeff = -1;
		b4.deg = {0,0,2,0,0};

		b.insert(b1); b.insert(b2); b.insert(b3); b.insert(b4);

		F.push_back(a);
		F.push_back(b);

		break;

// This is a twisted cubic
	case 2:
		indeterminates[0] = 't';
		indeterminates[1] = 'z';
		indeterminates[2] = 'y';
		indeterminates[3] = 'x';

		a1.coeff = -1;
		a1.deg = {1,0,0,0,0};

		a2.coeff = 1;
		a2.deg = {0,0,0,1,0};

		a.insert(a1); a.insert(a2);

		b1.coeff = -1;
		b1.deg = {2,0,0,0,0};

		b2.coeff = 1;
		b2.deg = {0,0,1,0,0};

		b.insert(b1); b.insert(b2);

		c1.coeff = -1;
		c1.deg = {3,0,0,0,0};

		c2.coeff = 1;
		c2.deg = {0,1,0,0,0};

		c.insert(c1); c.insert(c2);

		F.push_back(a);
		F.push_back(b);
		F.push_back(c);

		break;

// This is the same twisted cubic with different order
	case 3:
		indeterminates[0] = 't';
		indeterminates[1] = 'x';
		indeterminates[2] = 'y';
		indeterminates[3] = 'z';

		a1.coeff = -1;
		a1.deg = {1,0,0,0,0};

		a2.coeff = 1;
		a2.deg = {0,1,0,0,0};

		a.insert(a1); a.insert(a2);

		b1.coeff = -1;
		b1.deg = {2,0,0,0,0};

		b2.coeff = 1;
		b2.deg = {0,0,1,0,0};

		b.insert(b1); b.insert(b2);

		c1.coeff = -1;
		c1.deg = {3,0,0,0,0};

		c2.coeff = 1;
		c2.deg = {0,0,0,1,0};

		c.insert(c1); c.insert(c2);

		F.push_back(a);
		F.push_back(b);
		F.push_back(c);

		break;

// This is Enneper Surface
	case 4:
		indeterminates[0] = 'u';
		indeterminates[1] = 'v';
		indeterminates[2] = 'x';
		indeterminates[3] = 'y';
		indeterminates[4] = 'z';

		a1.coeff = 3;
		a1.deg = {1,0,0,0,0};

		a2.coeff = -1;
		a2.deg = {3,0,0,0,0};

		a3.coeff = 3;
		a3.deg = {1,2,0,0,0};

		a4.coeff = -1;
		a4.deg = {0,0,1,0,0};

		a.insert(a1); a.insert(a2); a.insert(a3); a.insert(a4);

		b1.coeff = 3;
		b1.deg = {0,1,0,0,0};

		b2.coeff = -1;
		b2.deg = {0,3,0,0,0};

		b3.coeff = 3;
		b3.deg = {2,1,0,0,0};

		b4.coeff = -1;
		b4.deg = {0,0,0,1,0};

		b.insert(b1); b.insert(b2); b.insert(b3); b.insert(b4); 

		c1.coeff = 3;
		c1.deg = {2,0,0,0,0};

		c2.coeff = -3;
		c2.deg = {0,2,0,0,0};

		c3.coeff = -1;
		c3.deg = {0,0,0,0,1};

		c.insert(c1); c.insert(c2); c.insert(c3); 

		F.push_back(a);
		F.push_back(b);
		F.push_back(c);

		break;

	default:
		cout << "Invalid case number." << endl;
		return 0;
	}


	cout << "Generators of the ideal :\n";
	for (auto &iter: F) cout << "  " << iter << "\n\n";

	G = Buchberger(F);  // compute Groebner basis

	cout << "\nGroebner basis of the ideal (size="<<G.size()<<") :\n";
	for (auto &iter: G) cout << "  " << iter << "\n\n";

	return 0;
}