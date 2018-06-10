#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include "stats.h"
typedef long long ll;

#define SEED 315

ll LCG(ll, ll, ll, ll);

int main()
{
	ll a = 32768+1;
	ll c = 3;
	ll m = 131072;
	ll arr1[m], arr2[m];
	double d_arr1[m], d_arr2[m];
	arr1[0] = SEED;
	ll cycle = m;

	for (ll i = 1; i < m; i++) {
		arr1[i] = LCG(arr1[i-1], a, c, m);
		arr2[i-1] = arr1[i];
	}
	arr2[m-1] = LCG(arr2[m-2], a, c, m);

	for (ll i = m-2; i >= 0; i--)
		if (arr1[m-1] == arr1[i]) { cycle = m-1-i; break; }
	for (ll i = 0; i < m; i++) {
		d_arr1[i] = (double)arr1[i]/m;
		d_arr2[i] = (double)arr2[i]/m;
	}

	printf("mean: %lf, stddev: %lf, cov: %lf\n"
		, mean(d_arr1, m), stddev(d_arr1, m), cov(d_arr1, d_arr2, m));
	printf("cycle: %lld\n", cycle);

	return 0;
}

ll LCG(ll X, ll a, ll c, ll m)
{
	return (a*X+c) % m;
}

