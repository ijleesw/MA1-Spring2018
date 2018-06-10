# Chinese Remainder Algorithm via Extended Euclidean Algorithm

Implementation of the Chinese remainder algorithm via [extended Euclidean algorithm](https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm).



## Description

```c++
// Function prototypes:
const vector<euclidean_ring> gcd_EEA(const euclidean_ring& a, const euclidean_ring& b);
const euclidean_ring CRT(const vector<euclidean_ring>& m, const vector<euclidean_ring>& v);
```

`gcd_EEA` returns a vector that contains gcd of `a` and `b` as the first component.

For `CRT`, [_i_-th component of `m`] and [the return value of `CRT`] are congruent modulo [_i_-th component of `v`].



## Implementation

`euclidean_ring` is supposed to be a polynomial ring that has `int leading_index()` as a member function and `vector<ring> coeff` as a member variable. Also, operator overloadings should be supported for `euclidean_ring` .

If you want to use types such as  `int` or `mpq_class` for `euclidean_ring`, then you should modify line 33 and 34 of `CRT_EEA.hpp`.



