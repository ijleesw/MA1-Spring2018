# Computing a Reduced Gröbner Basis

## 1. How to Run

Compile and run with the following command:

```bash
$ make
$ ./groebner <case number> (optional)-v
```

You need [GMP library](https://gmplib.org/manual/index.html#Top) to compile `main.cpp`.



The program computes reduced Gröbner basis for a given set of polynomials. You should modify `main.cpp` to input multivariate polynomials that generates the ideal.



There are only two cases available in `main.cpp`: Case #1 with _{x^3 - x, x^2 - y}_ and Case #2 with _{x^2y^2 + xy, y^4 - y^2}_.



`-v` option was used to debug codes. You can take a glimpse of how I debugged my codes with the option :)



## 2. High-Level Implementation

Implementation of multivariate monomial and polynomial can be found in `monomial.hpp` and `polynomial.hpp`, respectively.



The followings are some functions in `groebner.cpp` that are used to compute reduced Gröbner basis:

   \- `S_poly` computes S-polynomial of two polynomials that are given as parameters.

   \- `basis_dropout` computes minimal Gröbner basis of given Gröbner basis.

   \- `basis_reduction` computes reduced Gröbner basis of given Gröbner basis. `basis_dropout` is included in this function.

   \- `Groebner` computes reduced Gröbner basis of given polynomials (that are generators of an ideal). `basis_reduction` is included in this function.



## 3. Sample Output

```bash
$ ./groebner 1
a = ( 1 x^3 ) + ( -1 x^1 )
b = ( 1 x^2 ) + ( -1 y^1 )

S-polynomial(a,b) = ( 1 x^1 y^1 ) + ( -1 x^1 )

Groebner basis of F={a, b} :
 ( 1 x^2 ) + ( -1 y^1 )
 ( 1 x^1 y^1 ) + ( -1 x^1 )
 ( 1 y^2 ) + ( -1 y^1 )
```

