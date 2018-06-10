# Modulo Arithmetic for Z/pZ

Implement of modulo arithmetic for the field of characteristic _p_.



## 1. How to run

Compile and run with the following command:
```bash
$ make
$ ./modulo
```
You can change the prime _p_ by modifying line 4 of `Zp.hpp`. _p_ doesn't have to be a prime, but operator/ will not work properly in such case. (Assertion fails at line 64 of `Zp.hpp`.)



## 2. Sample Output

```bash
$ ./modulo
13+15=11
13-15=15
13*15=8
13/15=2
(13 == 15) = 0
(13 != 15) = 1
```




// TODO: Implement operations between `Zp` and `int`.