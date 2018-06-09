#ifndef SIMPLE_TAYLOR_HPP_
#define SIMPLE_TAYLOR_HPP_

#include <cmath>
#include "vector_tools.hpp"
#include "jet.hpp"
using namespace std;


/*****************************************************
 *
 *  Simple Taylor Method
 *
 *****************************************************/

template <typename R>
const vector< Jet<R> >
simple_taylor_step(const vector< Jet<R> > (*init_cond)(const vector< Jet<R> >&),
                   const vector<R> curr_val, const int taylor_deg)
{
	int k = 0;
	int init_size = curr_val.size();
	vector< Jet<R> > v(init_size, JET_INIT(taylor_deg+2));
	vector< Jet<R> > Dv(init_size, JET_INIT(taylor_deg+2));

	for (int i = 0; i < init_size; i++) {
		v[i].at(0) = curr_val[i];
	}

	while (k <= taylor_deg) {
		Dv = init_cond(v);
		for (int i = 0; i < init_size; i++) {
			v[i].at(k+1) += Dv[i].at(k)/(k+1);
		}
		k++;
	}

	return v;
}


template <typename R>
const vector< Jet<R> >
simple_taylor(const vector< Jet<R> > (*init_cond)(const vector< Jet<R> >&),
              const vector<R> init_val, const int taylor_deg,
              const R Point, const int steps, const bool verbose=false)
{
	int curr_step = 0;
	R step_size = Point/steps;
	int init_size = init_val.size();
	vector<R> curr_val = init_val;
	vector<R> err(init_size, 0);
	vector< Jet<R> > v(init_size, JET_INIT(taylor_deg+2));


	while ((curr_step++) < steps) {
		v = simple_taylor_step(init_cond, curr_val, taylor_deg);
		for (int i = 0; i < init_size; i++) {
			curr_val[i] = v[i].eval(step_size);
			err[i] = abs(v[i].at(taylor_deg+1)) * pow(step_size,taylor_deg+1);
		}

		if (verbose) {
			assert (init_size == 2);
			cout << "Step "<<curr_step<<", t = "<<curr_step*step_size<<endl;
			cout << "x(t) = " << curr_val[0] << "  w/ err: " << err[0] << endl;
			cout << "y(t) = " << curr_val[1] << "  w/ err: " << err[1] << endl;
			cout << endl;
		}
	}

	return v;
}


#endif /* SIMPLE_TAYLOR_HPP_ */