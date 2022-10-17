#ifndef KMEANS_H_
#define KMEANS_H_

#define N 10000000
#define Nc 100
#define Nv 1000
#define K 4

#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline","unsafe-math-optimizations")
#pragma GCC target("avx2","abm","bmi","bmi2","lzcnt","popcnt")
#pragma GCC option("arch=native","tune=native","no-zero-upper")

#include "../include/utils.h"

void k_means(point* samples, point* clusters);

#endif