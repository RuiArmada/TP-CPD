#ifndef CONST_H_
#define CONST_H_

#define N 10000000
#define K 4

// constants in this file are used to compile the code depending on the benchmark
// to be executed. The constants are defined in the Makefile and passed to the
// compiler using the -D option.

#ifndef CLUSTER_FUNC
#elif CLUSTER_FUNC < 1 || CLUSTER_FUNC > 9  // make sure the constant is in the correct range
// impl - 1
// impl_unrolled_2x - 2
// impl_unrolled_4x - 3 // default
// impl_unrolled_8x - 4
// impl_branchless - 5
// impl_branchless_unrolled_2x - 6
// impl_branchless_unrolled_4x - 7
// impl_branchless_unrolled_8x - 8
// impl omp simd - 9
// (WIP. Possible implementations using other simd instructions.)
#error "CLUSTER_FUNC must be in the range [1..8]. Defaults to 3."
#endif

#ifndef EUCLIDEAN_FUNC
#elif EUCLIDEAN_FUNC < 1 || EUCLIDEAN_FUNC > 3  // make sure the constant is in the correct range
// euclidean square root- 1
// euclidean squares sum - 2
// euclidean squares sum ompsimd - 3
// (WIP. Possible implementations using other simd instructions.)
#error "EUCLIDEAN_FUNC must be in the range [1..2]. Defaults to 2."
#endif

// if cluster == 9 && euclidean != 3 and vice versa, error out
#if (CLUSTER_FUNC == 9 && EUCLIDEAN_FUNC == 3) || (CLUSTER_FUNC != 9 && EUCLIDEAN_FUNC == 3)
#error "CLUSTER_FUNC and EUCLIDEAN_FUNC must both be set for simd. 9 and 3, respectively."
#endif

#endif