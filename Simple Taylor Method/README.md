# Simple Taylor Method via Jet

An implementation of simple Taylor method for initial value problem via [jet](https://bit.ly/2LzMAak). A _k_-jet is an element of _R[ε] / <ε^(k+1)>_.



## 1. How to Run

Compile and run with the following command:

```bash
$ make
$ ./simple_taylor
```



## 2. Description

The following is the prototype of `simple_taylor` function:

```c++
const vector< Jet<R> >
simple_taylor(const vector< Jet<R> > (*init_cond)(const vector< Jet<R> >&),
              const vector<R> init_val, const int taylor_deg,
              const R Point, const int steps, const bool verbose=false)
```

\- `*init_cond` is a function pointer of the given initial condition. `my_init_cond` in `main.cpp` is set to _v[0] = sin(x)_ and _v[1] = cos(x)_.

\- `init_val` has values of initial condition. In the given case, it is _{0, 1}_.

\- `taylor_deg` tells the degree of Taylor approximation.

\- `Point` is the point where the functions will be evaluated. If your `init_val` is evaluated at _a_ and you want to evaluate the functions at _b_, then set `Point` to _(b-a)_.

\- `steps` tells how many steps to take to reach `Point`. If `Point` is 6 and `steps` is 3, then the functions will be evaluated and re-expanded at 2, 4, and 6.

\- `verbose` tells `simple_taylor` whether or not to print intermediate/final results.



Lagrange form of the remainder is used to compute a guessed error; the error is computed at 0 to reduce computations.



## 3. Sample Output

```bash
$ ./simple_taylor
======================== Simple Taylor Method ========================
Step 1, t = 0.628319
x(t) = 0.587785  w/ err: 0
y(t) = 0.809017  w/ err: 2.82006e-17

Step 2, t = 1.25664
x(t) = 0.951057  w/ err: 1.65759e-17
y(t) = 0.309017  w/ err: 2.28148e-17

...

Step 5, t = 3.14159
x(t) = 8.97932e-11  w/ err: 1.65759e-17
y(t) = -1  w/ err: 2.28148e-17
```

