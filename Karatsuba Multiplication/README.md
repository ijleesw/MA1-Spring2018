# Implementation of Karatsuba Multiplication


## 1. How to run

Compile cpp file with the following command:
```bash
$ g++ -O3 -o Karatsuba Karatsuba.cpp
```
The size of polynomials can be set by modifying the following part of `Karatsuba.cpp`:
```c
#define EXP 15
#define DEG 32767 	//  should be 2^EXP-1. deg f and deg g equal DEG.
```


## 2. Sample Output

```bash
$ ./Karatsuba 
=====Karatsuba Multiplication=====
Time elapsed : 0.044655

=====Classical Multiplication=====
Time elapsed : 0.288335

isCorrect : true
```