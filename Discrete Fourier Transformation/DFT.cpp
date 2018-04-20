/*
 * Implementation of SFT and FFT.
 *
 * @ijleesw
 */
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <complex>
#include <string.h>
using namespace std;

int N;
int logN;

complex<double>* poly_f;
complex<double>* poly_g;
complex<double>* poly_h;

complex<double>* DFT_f;
complex<double>* DFT_g;
complex<double>* DFT_h;

complex<double>* roots;
complex<double>* roots_inv;
complex<double> **_temp_;


// initializes arrays
void init();

// repeated squaring algorithm
template <typename generic_float>
generic_float rpower(generic_float x, int exp);

// SFT with Vandermonde matrix
void SFT(complex<double> *, complex<double> *);
void SFT_inv(complex<double> *, complex<double> *);

// FFT using recursion
void FFT(complex<double> *, complex<double> *, complex<double> **);
void FFT_inv(complex<double> *, complex<double> *, complex<double> **);
void FFThelper(int, int, complex<double> **, bool);


// main function
int main(int argc, char **argv)
{
	/* Step 0. Setups */
	if (argc <= 1) {
		cout << "Requires the power of two as an argument. ex) ./DFT 16" << endl;
		return 0;
	}

	N = atoi(argv[1]);		// N should be the power of 2
	logN = 0;
	while((int)pow(2,++logN) < N);

	init(); // Receives input in init function

	/* Step 1. Choose between SFT and FFT */
	int choice = 0;
	while ((choice+1)/2 != 1) {
		cout << "SFT(1), FFT(2) : ";
		cin >> choice;
	}

	/* Step 2. Apply DFT */
	if (choice == 1) {
		SFT(DFT_f, poly_f);
		SFT(DFT_g, poly_g);		
	}
	if (choice == 2) {
		FFT(DFT_f, poly_f, _temp_);
		FFT(DFT_g, poly_g, _temp_);
	}

	/* Step 3. Apply componentwise multiplication */
	for (int i = 0; i < N; i++) {
		DFT_h[i] = DFT_f[i] * DFT_g[i];
	}

	/* Step 4. Apply inverse DFT */
	if (choice == 1) SFT_inv(poly_h, DFT_h);
	if (choice == 2) FFT_inv(poly_h, DFT_h, _temp_);

	/* Print the result */
	for (int i = 0; i < min(N-1,10); i++) {
		cout << "( (" << poly_h[i].real() << ") + ";
		cout << "(" << poly_h[i].imag() << ")i ) ";
		cout << "x^" << i << " + " << endl;
	}
	if (N > 11) cout << "( ... ) + " << endl;
	cout << "( (" << poly_h[N-1].real() << ") + ";
	cout << "(" << poly_h[N-1].imag() << ")i ) ";
	cout << "x^" << N-1 << endl;


	free(poly_f);
	free(poly_g);
	free(poly_h);
	free(DFT_f);
	free(DFT_g);
	free(DFT_h);
	free(roots);
	free(roots_inv);

	return 0;
}


/*
 * init: initializes arrays
 */
void init()
{
	poly_f = (complex<double>*)calloc(N, sizeof(complex<double>));
	poly_g = (complex<double>*)calloc(N, sizeof(complex<double>));
	poly_h = (complex<double>*)calloc(N, sizeof(complex<double>));
	
	DFT_f = (complex<double>*)calloc(N, sizeof(complex<double>));
	DFT_g = (complex<double>*)calloc(N, sizeof(complex<double>));
	DFT_h = (complex<double>*)calloc(N, sizeof(complex<double>));

	roots = (complex<double>*)calloc(N, sizeof(complex<double>));
	roots_inv = (complex<double>*)calloc(N, sizeof(complex<double>));

	_temp_ = (complex<double>**)malloc((logN+1)*sizeof(complex<double>*));
	for (int i = 0; i < logN+1; i++) _temp_[i] = (complex<double>*)calloc(N, sizeof(complex<double>));

	complex<double> expo = 2i * M_PI / (double)N;
	complex<double> w = exp(expo);

	roots[0] = 1;
	roots_inv[0] = 1;
	for (int i = 1; i < N; i++) roots_inv[N-i] = roots[i] = roots[i-1]*w;

	ifstream _read("input.txt");
	for (int i = 0; i < N; i++) _read >> poly_f[i];
	for (int i = 0; i < N; i++) _read >> poly_g[i];
	_read.close();
}

/*
 * @input  : x, exp
 * @output : power(x,exp)
 */
template <typename generic_float>
generic_float rpower(generic_float x, int exp)
{
	if (exp == 0) return 1;
	else if (exp & 1) return x * rpower(x, exp/2);
	else {
		generic_float tmp = rpower(x, exp/2);
		return tmp*tmp;
	}
}

/*
 * @input  : _DFT_f, _poly_f
 * @output : _DFT_f = SFT(_poly_f)
 */
void SFT(complex<double> * _DFT_f, complex<double> * _poly_f)
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int exp = (i*j) % N;
			_DFT_f[i] += _poly_f[j] * roots[exp];
		}
	}
}

/*
 * @input  : _poly_f, _DFT_f
 * @output : _poly_f = DFT^(-1)(_DFT_f)
 */
void SFT_inv(complex<double> * _poly_f, complex<double> * _DFT_f)
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int exp = (i*j) % N;
			exp = (N - exp) % N;
			_poly_f[i] += _DFT_f[j] * roots[exp];
		}
		_poly_f[i] /= (double)N;
	}
}

/*
 * @input  : _DFT_f, _poly_f
 * @output : _DFT_f = FFT(_poly_f)
 */
void FFT(complex<double> * _DFT_f, complex<double> * _poly_f, complex<double> ** __temp__)
{
	memcpy(__temp__[0], _poly_f, N*sizeof(complex<double>));
	FFThelper(0, 0, __temp__, false);

	for (int i = 0; i < N; i++) {
		int _i = i;
		int cnt = 0;
		int size = N;
		while (_i > 0) {
			size /= 2;
			cnt += (_i%2) * size;
			_i /= 2;
		}
		_DFT_f[i] = __temp__[logN][cnt];
	}
}

/*
 * @input  : _poly_f, _DFT_f
 * @output : _poly_f = DFT^(-1)(_DFT_f)
 */
void FFT_inv(complex<double> * _poly_f, complex<double> * _DFT_f, complex<double> ** __temp__)
{
	memcpy(__temp__[0], _DFT_f, N*sizeof(complex<double>));
	FFThelper(0, 0, __temp__, true);

	for (int i = 0; i < N; i++) {
		int _i = i;
		int cnt = 0;
		int size = N;
		while (_i > 0) {
			size /= 2;
			cnt += (_i%2) * size;
			_i /= 2;
		}
		_poly_f[i] = __temp__[logN][cnt] / (double)N;
	}
}

/*
 * @input  : depth, startpoint, *__temp__, is_inv
 * @output : __temp__[logN] filled with components of DFT(__temp__[0]) (From FFT/FFT_inv's viewpoint)
 */
void FFThelper(int depth, int startpoint, complex<double> ** __temp__, bool is_inv)
{
	int curr_size = N/(int)pow(2,depth);
	int next_size = curr_size/2;

	if (next_size == 0) return;

	for (int i = 0; i < next_size; i++) {
		__temp__[depth+1][startpoint+i] = __temp__[depth][startpoint+i] + __temp__[depth][startpoint+next_size+i];

		if (!is_inv) {
			__temp__[depth+1][startpoint+next_size+i] =
			        (__temp__[depth][startpoint+i]-__temp__[depth][startpoint+next_size+i]) * roots[i * (N/(2*next_size))];
		}
		else {
			__temp__[depth+1][startpoint+next_size+i] =
					(__temp__[depth][startpoint+i]-__temp__[depth][startpoint+next_size+i]) * roots_inv[i * (N/(2*next_size))];
		}
	}

	if (!is_inv) {
		FFThelper(depth+1, startpoint, __temp__, false);
		FFThelper(depth+1, startpoint+next_size, __temp__, false);
	}
	else {
		FFThelper(depth+1, startpoint, __temp__, true);
		FFThelper(depth+1, startpoint+next_size, __temp__, true);
	}
}
