# Buchberger Algorithm for Reduced Gröbner Basis

## 1. How to Run

Compile and run with the following command:

```bash
$ make
$ ./groebner <case number> (optional)-v
```

You need [GMP library](https://gmplib.org/manual/index.html#Top) to compile `main.cpp`.



The program computes reduced Gröbner basis for a given set of polynomials. There are 4 cases available in `main.cpp`.

   \- case 1: _\<x^2 + y^2 + z^2 - 1, x^3 + x^2 - y^2 - z^2\>_ with lexicographic order _x > y > z_.

   \- case 2: (twisted cubic) _\<-t + x, -t^2 + y, -t^3 + x\>_ with lexicographic order _t > z > y > x_.

   \- case 3: (twisted cubic) _\<-t + x, -t^2 + y, -t^3 + x\>_ with lexicographic order _t > x > y > z_. 

   \- case 4: (Enneper Surface) _\<-u^3 + 3u(v^2) + 3u - x, 3(u^2)v - v^3 + 3v - y, 3u^2 - 3v^2 - z\>_ with lexicographic order _u > v > x > y > z_.

You can modify `main.cpp` to input multivariate polynomials that generates the ideal. Don't forget to change the value of `N` in line 6 when you use more than 5 indeterminates.



If you want a monomial with lower degree comes before, use `$ make reverse`.

`-v` option is used to check epoches of loops in `Buchberger` function. _You shall not change the order of arguments._



## 2. High-Level Implementation

Implementation of multivariate monomial and polynomial can be found in `monomial.hpp` and `polynomial.hpp`, respectively.



The followings are some functions in `buchberger.cpp` and `polynomial.hpp` that are used to compute reduced Gröbner basis:

   \- `polynomial::bar_`  returns a division of _(*this)_ by a set of polynomials.

   \- `S_poly` computes S-polynomial of two polynomials that are given as parameters.

   \- `basis_dropout` computes minimal Gröbner basis of given Gröbner basis.

   \- `basis_reduction` computes reduced Gröbner basis of given Gröbner basis. `basis_dropout` is included in this function.

   \- `Buchberger` computes reduced Gröbner basis of given polynomials (which are generators of an ideal). `basis_reduction` is included in this function.





## 3. Sample Output

```bash
$ ./groebner 1
Generators of the ideal :
  ( 1 x^2 ) + ( 1 y^2 ) + ( 1 z^2 ) + ( -1 )

  ( 1 x^3 ) + ( 1 x^2 ) + ( -1 y^2 ) + ( -1 z^2 )


Groebner basis of the ideal (size=2) :
  ( 1 x^1 ) + ( -1 y^4 ) + ( -2 y^2 z^2 ) + ( -2 y^2 ) + ( -1 z^4 ) + ( -2 z^2 ) + ( 1 )

  ( 1 y^6 ) + ( 3 y^4 z^2 ) + ( 1 y^4 ) + ( 3 y^2 z^4 ) + ( 2 y^2 z^2 ) + ( -1 y^2 ) + ( 1 z^6 ) + ( 1 z^4 ) + ( -1 z^2 )
```

