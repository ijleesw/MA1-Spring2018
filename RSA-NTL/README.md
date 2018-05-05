# Implementation of RSA Cryptosystem using NTL Library

## 1. How to Run

Compile cpp file with the following command:

```bash
g++ -O2 -std=c++11 -pthread -march=native -o RSA main.cpp -lntl -lgmp -lm
```

You need [NTL library](http://www.shoup.net/ntl/) and [GMP library](https://gmplib.org/manual/index.html#Top) to compile main.cpp.



The program receives your input message and dynamically generates prime numbers p and q for RSA cryptosystem.



For each variable initialized with `GenPrime_ZZ`, the probability of the variable not being a prime is bounded by 2^(-ERR). `ERR` is defined in the first line of the source file.



Each user in the cryptosystem is represented by `class User` so it's easy to extend the code to multi-user cases. The class has `send_to`, `receive`, `decrypt`, and `announce` as only public methods. Each method's functionality is easy to understand when you see the code, so detailed explanation omitted.



## 2. Sample Output

```bash
$ ./RSA
Type Alice's message: 	1125899906842624
Alice's encrypted message: 	5277132820350435844
Bob's decrypted message: 	1125899906842624
```

