#include <iostream>
#include "vector_tools.hpp"
#include "simple_taylor.hpp"

typedef long double R;
using namespace std;


/*****************************************************
 *
 *  Initial condition definition
 *
 *****************************************************/

const vector< Jet<R> > my_init_cond(const vector< Jet<R> >& v)
{
	int v_size = v.size();
	int jet_length = v[0].length();
	vector< Jet<R> > Dv(v_size, JET_INIT(jet_length));

	Dv[0] = v[1];		// v[0] = sin(x)
	Dv[1] = v[0]*(-1);	// v[1] = cos(x)
	
	return Dv;
}


/*****************************************************
 *
 *  Main function
 *
 *****************************************************/

int main(int argc, char** argv)
{
	vector<R> init_val = {0, 1};
	int taylor_deg = 15;
	R Point = 3.1415926535;
	int steps = 5;

	cout << "======================== Simple Taylor Method ========================" << endl;
	simple_taylor(my_init_cond, init_val, taylor_deg, Point, steps, true);
	/*
	 * To obtain (taylor_deg)-degree Taylor approximation for each function, use
	 * vector< Jet<R> > v = simple_taylor(my_init_cond, init_val, taylor_deg, Point, steps)
	 */

	return 0;
}
