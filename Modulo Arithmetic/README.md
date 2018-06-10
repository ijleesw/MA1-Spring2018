# Modulo Arithmetic for Z/pZ

Implement of modulo arithmetic for the field of characteristic _p_.



## 1. How to run

Compile and run with the following command:
```bash
$ make
$ ./modulo
```
You can change the prime _p_ by modifying line 4 of `Zp.hpp`. _p_ doesn't have to be a prime, but don't forget to change `isField` in line 5 if _p_ is not a prime. `operator/` should be disabled in such cases.



## 2. Sample Output

```bash
$ ./modulo
Welcome to the world of modulo arithmetic!
13+15=11
13-15=15
13*15=8
13/15=2
(13==15)=0
(13!=15)=1
```



// TODO: Implement operations between `Zp` and `int`.