/*
 * To compile and link, use the following command:
 * $ make
 *
 * If you want a monomial with lower degree comes before, use the following command:
 * $ make reverse
 */
#define N 5 	// # of indeterminates

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

char indeterminates[N] = {'u', 'v', 'x', 'y', 'z'}; 	// array of the name of indeterminates

bool verbose = false;

/************************************************
 *
 *  Main function
 *
 ************************************************/

int main(int argc, char** argv)
{
	vector<Q> input(N);
	monomial<Q> a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3;

	polynomial< Q, monomial<Q> > a, b, c, d, EMPTY;

	if (argc < 2) {
		cout << "Input command should be";
		cout << "  "<<argv[0]<<" <case number> (optional)-v" << endl;
		return 0;
	}

	if (argc >=3 && strcmp(argv[2], "-v") == 0) verbose = true;

	switch (atoi(argv[1])) {
/*
// Use the following:
// #define N 2 	// # of indeterminates
// char indeterminates[N] = {'x', 'y'};
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
// Use the following:
// #define N 2 	// # of indeterminates
// char indeterminates[N] = {'x', 'y'};
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
*/
	case 3:
// Use the following:
// #define N 5 	// # of indeterminates
// char indeterminates[N] = {'u', 'v', 'x', 'y', 'z'};
		a1.coeff = -1;
		//a1.deg = {0,0,0,1,0};
		a1.deg = {1,0,0,0,0};

		a2.coeff = "1/3";
		a2.deg = {3,0,0,0,0};

		a3.coeff = -1;
		a3.deg = {1,2,0,0,0};

		a4.coeff = 1;
		a4.deg = {0,0,1,0,0};

		a.insert(a1); a.insert(a2); a.insert(a3); a.insert(a4);


		b1.coeff = 1;
		b1.deg = {0,1,0,0,0};

		b2.coeff = "-1/3";
		b2.deg = {0,3,0,0,0};

		b3.coeff = 1;
		b3.deg = {2,1,0,0,0};

		b4.coeff = 1;
		b4.deg = {0,0,0,1,0};

		b.insert(b1); b.insert(b2); b.insert(b3); b.insert(b4); 


		c1.coeff = -1;
		c1.deg = {2,0,0,0,0};

		c2.coeff = 1;
		c2.deg = {0,2,0,0,0};

		c3.coeff = 3;
		c3.deg = {0,0,0,0,1};

		c.insert(c1); c.insert(c2); c.insert(c3); 

		break;
/*
	case 4:
// Use the following:
// #define N 4 	// # of indeterminates
// char indeterminates[N] = {'t', 'z', 'y', 'x', 'w'};

		a1.coeff = 1;
		a1.deg = {3,0,0,0,0};

		a2.coeff = -1;
		a2.deg = {0,1,0,0,0};

		a.insert(a1); a.insert(a2);

		b1.coeff = 1;
		b1.deg = {2,0,0,0,0};

		b2.coeff = -1;
		b2.deg = {0,0,1,0,0};

		b.insert(b1); b.insert(b2);

		c1.coeff = 1;
		c1.deg = {1,0,0,0,0};

		c2.coeff = -1;
		c2.deg = {0,0,0,1,0};

		c.insert(c1); c.insert(c2);

		break;
*/
	case 5:
// Use the following:
// #define N 5 	// # of indeterminates
// char indeterminates[N] = {'u', 'v', 'x', 'y', 'z'};
		a1.coeff = 3;
		//a1.deg = {0,0,0,1,0};
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

		break;

	default:
		cout << "Invalid case number." << endl;
		return 0;
	}
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	if (c != EMPTY) cout << "c = " << c << endl << endl;

	//cout << "S-polynomial(a,b) = " << S_poly(a, b) << endl << endl;

	vector< polynomial< Q, monomial<Q> > > F, G;
	F.push_back(a);
	F.push_back(b);
	F.push_back(c);
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

	cout << "Groebner basis of F={a, b} (size = "<<G.size()<<") : " << endl;
	for (auto &iter: G) cout << " " << iter << endl;
	cout << endl;

	return 0;
}