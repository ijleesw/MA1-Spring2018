# Pseudorandom Number Generators

Implement of [linear congruence generator](https://en.wikipedia.org/wiki/Linear_congruential_generator), [middle square method](https://en.wikipedia.org/wiki/Middle-square_method), and [lagged fibonacci generator](https://en.wikipedia.org/wiki/Lagged_Fibonacci_generator).



## 1. How to run

Compile and run with the following command:
```bash
$ make
$ ./lcg
$ ./msm
$ ./lfg
```


## 2. Sample Output

```bash
$ ./lcg
mean: 0.499996, stddev: 0.288675, cov: 0.005208
cycle: 131072
$ ./msm
mean: 0.521326, stddev: 0.299526, cov: -0.000572
cycle: 300
$ ./lfg
mean: 0.500124, stddev: 0.288779, cov: -0.000473
cycle: 100000
```


