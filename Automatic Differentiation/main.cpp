#include <iostream>
#include "dual.hpp"
using namespace std;

typedef double ring;

dual<ring> f(dual<ring> x)
{
	cout << "f(x) = (x+1)^(2x)" << endl;
	return pow(x+1, x*2);
}

int main(int argc, char** argv)
{
	ring a = 0.7;
	dual<ring> y = f(X(a));

	cout << "Value of f at "<<a<<" : " << y.val << endl;
	cout << "Derivative of f at "<<a<<" : " << y.deriv << endl;

	return 0;
}