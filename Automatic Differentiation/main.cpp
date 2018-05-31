#include <iostream>
#include "dual.hpp"
using namespace std;

typedef double ring;

dual<ring> f(dual<ring> X)
{
	cout << "f(x) = (x+1)^(x+1)" << endl;
	return pow(X+CONST(1), X+CONST(1));
}

int main(int argc, char** argv)
{
	ring a = 0.5;
	dual<ring> y = f(X(a));

	cout << "Value of f at "<<a<<" : " << y.val << endl;
	cout << "Derivative of f at "<<a<<" : " << y.deriv << endl;

	return 0;
}