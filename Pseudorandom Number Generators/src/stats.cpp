#include <cmath>
#include "stats.h"

typedef long long ll;

double mean(double *arr, ll size)
{
	double res = 0;
	for (ll i = 0; i < size; i++)
		res += arr[i];
	return res/size;
}

double stddev(double *arr, ll size)
{
	double m = mean(arr, size);
	double res = 0;
	for (ll i = 0; i < size; i++)
		res += pow(arr[i]-m, 2);
	return sqrt(res/size);
}

double cov(double *arr1, double *arr2, ll size)
{
	double m1 = mean(arr1, size);
	double m2 = mean(arr2, size);
	double res = 0;

	for (ll i = 0; i < size; i++)
		res += (m1-arr1[i]) * (m2-arr2[i]);
	res /= size;
	return res;
}