# Computing a Reduced Gröbner Basis

## 1. How to Run

Compile and run with the following command:

```bash
$ make
$ ./groebner <case number> (optional)-v
```

You need [GMP library](https://gmplib.org/manual/index.html#Top) to compile `main.cpp`.



The program computes reduced Gröbner basis for a given set of polynomials. You should modify `main.cpp` to input multivariate polynomials that generates the ideal.



There are a few cases available in `main.cpp`. You should see the code to check available cases. For example, Case 3 is [Enneper space](https://en.wikipedia.org/wiki/Enneper_surface) with _u > v > x > y > z_.



If you want a monomial with lower degree comes before, type `$ make reverse` to compile.



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
$ ./groebner 4
a = ( 1 t^3 ) + ( -1 z^1 )
b = ( 1 t^2 ) + ( -1 y^1 )
c = ( 1 t^1 ) + ( -1 x^1 )

Epoch : 1
  Sub Epoch : 1
  Sub Epoch : 2
Epoch : 2
  Sub Epoch : 1
  Sub Epoch : 2
  Sub Epoch : 3
  Sub Epoch : 4
Groebner basis of F={a, b} (size = 3) :
 ( 1 t^1 ) + ( -1 x^1 )
 ( 1 z^1 ) + ( -1 x^3 )
 ( 1 y^1 ) + ( -1 x^2 )
```

