# Automatic Differentiation

An implementation of automatic differentiation via an operator overloading of dual number.



## 1. How to Run

Compile and run with the following command:

```bash
$ g++ -o autodiff main.cpp
$ ./autodiff
```

To calculate the derivative of your favorite function _f_ at some point _a_, namely _f'(a)_, modify the function `f` and the value of `a` in `main.cpp`

Lists of macro(s) and pre-defined functions can be found in `dual.hpp`.



## 2. Description

`class dual` contains two ring elements: `val` and `deriv`. Every time an operator or a function is applied, the result is stored in `val` and the derivative is stored in `deriv`.

Apply whatever function you want and get derivative by just checking `deriv`.



## 3. Sample Output

```bash
$ ./autodiff
f(x) = x^x
Value of f at 0.5 : 0.707107
Derivative of f at 0.5 : 0.216978
```

