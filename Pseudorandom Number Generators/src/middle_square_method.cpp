#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include "stats.h"
typedef long long ll;

#define SEED 10101010
#define SIZE 8
#define EPOCH 300

ll MSM(ll);

int main()
{
	ll arr1[EPOCH], arr2[EPOCH];
	double d_arr1[EPOCH], d_arr2[EPOCH];
	arr1[0] = SEED;
	ll cycle = EPOCH;

	for (ll i = 1; i < EPOCH; i++) {
		arr1[i] = MSM(arr1[i-1]);
		arr2[i-1] = arr1[i];
	}
	arr2[EPOCH-1] = MSM(arr2[EPOCH-2]);

	for (ll i = EPOCH-2; i >= 0; i--)
		if (arr1[EPOCH-1] == arr1[i]) { cycle = EPOCH-1-i; break; }
	for (ll i = 0; i < EPOCH; i++) {
		d_arr1[i] = (double)arr1[i]/pow(10, SIZE);
		d_arr2[i] = (double)arr2[i]/pow(10, SIZE);
	}

	printf("mean: %lf, stddev: %lf, cov: %lf\n"
		, mean(d_arr1, EPOCH), stddev(d_arr1, EPOCH), cov(d_arr1, d_arr2, EPOCH));
	printf("cycle: %lld\n", cycle);

	return 0;
}

ll MSM(ll X)
{
	return (ll)((X*X) / pow(10, SIZE/2)) % (ll)pow(10, SIZE);
}

