#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include "stats.h"
typedef long long ll;

#define SEED 315
#define EXP 17
#define EPOCH 100000
#define M pow(2,EXP)
#define L 24
#define K 55

ll LFG(ll *, ll);
ll LCG(ll, ll, ll, ll);

int main()
{
	ll a = 32768+1;
	ll c = 3;
	ll arr1[EPOCH], arr2[EPOCH];
	double d_arr1[EPOCH], d_arr2[EPOCH];
	arr1[0] = SEED;
	ll cycle = EPOCH;

// fill from x_0 to x_{k-1}
	for (ll i = 1; i < K; i++) {
		arr1[i] = LCG(arr1[i-1], a, c, M);
		arr2[i-1] = arr1[i];
	}
	arr2[EPOCH-1] = LCG(arr2[EPOCH-2], a, c, M);


// generate pseudo-random number
	for (ll i = K; i < EPOCH; i++) {
		arr1[i] = LFG(arr1, i);
		arr2[i-1] = arr1[i];
	}
	arr2[EPOCH-1] = LFG(arr2, EPOCH-1);

	for (ll i = EPOCH-2; i >= 0; i--)
		if (arr1[EPOCH-1] == arr1[i]) { cycle = EPOCH-1-i; break; }
	for (ll i = 0; i < EPOCH; i++) {
		d_arr1[i] = (double)arr1[i]/pow(2, EXP);
		d_arr2[i] = (double)arr2[i]/pow(2, EXP);
	}

	printf("mean: %lf, stddev: %lf, cov: %lf\n"
		, mean(d_arr1, EPOCH), stddev(d_arr1, EPOCH), cov(d_arr1, d_arr2, EPOCH));
	printf("cycle: %lld\n", cycle);

	return 0;
}

ll LFG(ll *arr, ll curr)
{
	return (arr[curr-L] + arr[curr-K]) % (ll)pow(2, EXP);
}

ll LCG(ll X, ll a, ll c, ll m) { return (a*X+c) % m; }

