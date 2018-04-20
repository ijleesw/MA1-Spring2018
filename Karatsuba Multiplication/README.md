# Implementation of Karatsuba Multiplication


## How to run

Compile cpp file with the following command:
```bash
g++ Karatsuba.cpp -O3 -o Karatsuba
```
The size of polynomials can be set by modifying the following part of `Karatsuba.cpp`:
```c
#define EXP 15
#define DEG 32767 	//  should be 2^EXP-1. deg f and deg g equal DEG.
```


## Example Result

```bash
$ ./Karatsuba 
=====Karatsuba Multiplication=====
Time elapsed : 0.044655

=====Classical Multiplication=====
Time elapsed : 0.288335

isCorrect : true
```