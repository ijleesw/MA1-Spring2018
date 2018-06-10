#include <iostream>
#include "Zp.hpp"
using namespace std;

int main()
{
	Zp a = 13;
	Zp b = 15;

	cout << "Welcome to the world of modulo arithmetic" << endl;

	cout << a<<"+"<<b<<"="<<a+b << endl;
	cout << a<<"-"<<b<<"="<<a-b << endl;
	cout << a<<"*"<<b<<"="<<a*b << endl;
	cout << a<<"/"<<b<<"="<<a/b << endl;

	cout << "("<<a<<" == "<<b<<") = "<<(a == b) << endl;
	cout << "("<<a<<" != "<<b<<") = "<<(a != b) << endl;

	cout << Zp(12)/Zp(17) << endl;  // Assertion fails

	return 0;
}