# Multivariate Polynomial

Implementation of multivariate polynomial with lexicographcal order.



## 1. How to run

Compile and run with the following command:
```bash
$ g++ -std=c++11 -o multivariate main.cpp -lgmp -lgmpxx
$ ./multivariate
```


## 2. Description

`class polynomial` has one variable and `class monomial` has two variables:

```c++
class polynomial
{
public:
	list<monomial> terms;
    ...
}

class monomial
{
public:
	ring coeff = 0;
	vector<int> deg;
    ...
}
```

`class monomial` supports `operator<` and `operator>`; they just call `lexCompareTo`. If you want some other orderings, add ordering function in `class monomial` and call that function in those operators. See `polynomial.hpp` for member functions of `class polynomial`.



The number of indeterminates is originally set to 3. If you want to change it, modify line 1 and line 15 of `main.cpp` :

```c++
#define N 3  // # of indeterminates (<- line 1)
...
char indeterminates[N] = {'x', 'y', 'z'};  // name of indeterminates (<- line 15)
```



This multivariate polynomial class code was originally written for Buchberger algorithm, so detailed usage can be found in the corresponding directory.



## 3. Sample Output

```bash
$ ./multivariate
a(x, y, z) = ( 15/31 x^16 y^11 z^13 ) + ( -77/4 x^8 y^88 z^76 ) + ( 12 x^2 y^3 z^8 )
b(x, y, z) = ( 7749/8 x^10 y^15 z^15 ) + ( -12 x^2 y^3 z^8 )

a+b = ( 15/31 x^16 y^11 z^13 ) + ( 7749/8 x^10 y^15 z^15 ) + ( -77/4 x^8 y^88 z^76 )
a-b = ( 15/31 x^16 y^11 z^13 ) + ( -7749/8 x^10 y^15 z^15 ) + ( -77/4 x^8 y^88 z^76 ) + ( 24 x^2 y^3 z^8 )
a*b = ( 116235/248 x^26 y^26 z^28 ) + ( -596673/32 x^18 y^103 z^91 ) + ( -180/31 x^18 y^14 z^21 ) + ( 23247/2 x^12 y^18 z^23 ) + ( 231 x^10 y^91 z^84 ) + ( -144 x^4 y^6 z^16 )
```


