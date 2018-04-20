/*
 * Karatsuba Multiplication
 *
 * @ijleesw
 */
#define EXP 15
#define DEG 32767 	// should be 2^EXP-1. deg f and deg g equal DEG.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
using namespace std;

int f[DEG+1];
int g[DEG+1];
int res_karatsuba[DEG*2+2] = {0,};
int res_classical[DEG*2+2] = {0,};

int* v_upper[EXP+1];
int* v_lower[EXP+1];
int* w_upper[EXP+1];
int* w_lower[EXP+1];

int* z0[EXP+1];
int* z1[EXP+1];
int* z2[EXP+1];

int tmp_add_1[DEG+1];
int tmp_add_2[DEG+1];

void init();

void lowerhalf(int*, int);
void upperhalf(int*, int);

void polynomial_addition(int*, int*, int*, int);

void karatsuba_multiplication(int*, int*, int*, int);
void classical_multiplication(int*, int*, int*, int);


int main()
{
	int i;
	clock_t tic, toc;
	double time_k, time_c;
	//ofstream _write("output.txt", ios::app);
	bool isCorrect;

	init();

	cout << "=====Karatsuba Multiplication=====\n";
	tic = clock();
	karatsuba_multiplication(res_karatsuba, f, g, 0);
	toc = clock();
	time_k = (double)(toc-tic) / CLOCKS_PER_SEC;
	cout << "Time elapsed : " << time_k;
	cout << endl << endl;


	cout << "=====Classical Multiplication=====\n";
	tic = clock();
	classical_multiplication(res_classical, f, g, DEG+1);
	toc = clock();
	time_c = (double)(toc-tic) / CLOCKS_PER_SEC;
	cout << "Time elapsed : " << time_c;
	cout << endl << endl;


	cout << "isCorrect : ";	
	isCorrect = true;
	for (i = 0; i <= DEG*2; i++) {
		if (res_karatsuba[i] != res_classical[i]) {
			isCorrect = false;
			break;
		}
	}
	if (isCorrect) cout << "true" << endl;
	else cout << "false" << endl;

	
	//_write << "Degree : " << DEG << endl;
	//_write << "Karat : " << time_k << " / Classic : " << time_c << endl << endl;

	//_write.close();

	return 0;
}


/*
 * Initializes polynomials
 */
void init()
{
	int i;
	for (i = 0; i <= DEG; i++) {
		f[i] = i+1;
		g[i] = DEG-i+1;
	}
	for (i = 0; i <= EXP; i++) {
		int size = (int)pow(2,EXP-i);
		v_upper[i] = (int*)calloc(size+2, sizeof(int));
		v_lower[i] = (int*)calloc(size+2, sizeof(int));
		w_upper[i] = (int*)calloc(size+2, sizeof(int));
		w_lower[i] = (int*)calloc(size+2, sizeof(int));

		z0[i] = (int*)calloc(2*size+2, sizeof(int));
		z1[i] = (int*)calloc(size+2, sizeof(int));
		z2[i] = (int*)calloc(size+2, sizeof(int));
	}
}


/*
 * Returns lower half of the given polynomial
 */
void lowerhalf(int* res, int* v, int depth)
{
	int i;
	int size = (int)pow(2,EXP-depth);
	for (i = 0; i < size; i++) res[i] = v[i];
}

/*
 * Returns upper half of the given polynomial
 */
void upperhalf(int* res, int* v, int depth)
{
	int i;
	int size = (int)pow(2,EXP-depth);
	for (i = 0; i < size; i++) res[i] = v[i+size];
}


/*
 * Returns an addition of two polynomials v and w
 */
void polynomial_addition(int* res, int* v, int* w, int size)
{
	int i;
	for (i = 0; i < size; i++) res[i] = v[i] + w[i];
}


/*
 * Returns a multiplication of two polynomials v and w
 * computed via karatsuba multiplication
 */
void karatsuba_multiplication(int* res, int* v, int* w, int depth)
{
	int i;
	int size = (DEG+1)/(int)pow(2,depth);
	int mid = size / 2;

	int THRES = 64;
	if (size <= THRES) classical_multiplication(res, v, w, size);

	else {
		upperhalf(v_upper[depth+1], v, depth+1);
		lowerhalf(v_lower[depth+1], v, depth+1);
		upperhalf(w_upper[depth+1], w, depth+1);
		lowerhalf(w_lower[depth+1], w, depth+1);

		karatsuba_multiplication(z2[depth],
								 v_upper[depth+1], w_upper[depth+1], depth+1);

		karatsuba_multiplication(z0[depth],
								 v_lower[depth+1], w_lower[depth+1], depth+1);

		polynomial_addition(tmp_add_1, v_lower[depth+1], v_upper[depth+1], mid);
		polynomial_addition(tmp_add_2, w_lower[depth+1], w_upper[depth+1], mid);

		karatsuba_multiplication(z1[depth], tmp_add_1, tmp_add_2, depth+1);

		memcpy(res, z0[depth], 2*size*sizeof(int));
		for (i = 0; i < size; i++) {
			res[i+mid] += z1[depth][i] - (z0[depth][i] + z2[depth][i]);
			res[i+2*mid] += z2[depth][i];
		}
	}
}


/*
 * Returns a multiplication of two polynomials v and w
 * computed via classical multiplication
 */
void classical_multiplication(int* res, int* v, int* w, int size)
{
	int i;
	memset(res, 0, 2*size*sizeof(int));
	for (i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			res[i+j] += v[i] * w[j];
		}
	}
}
