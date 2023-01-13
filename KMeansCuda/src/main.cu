#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/kmeans.cuh"

void generate_samples(sample* sx, cluster* cx, const uint32_t N, const uint32_t K) {
    srand(10);

    for (uint_fast32_t i = 0; i < N; i += 1) {
        sx[i].x = (float)rand() / RAND_MAX;
        sx[i].y = (float)rand() / RAND_MAX;
        sx[i].id = 0;
    }

    for (uint_fast32_t i = 0; i < K; i += 1) {
        cx[i].x = sx[i].x;
        cx[i].y = sx[i].y;
        cx[i]._c = 0;
        cx[i]._x = 0;
        cx[i]._y = 0;
    }
}

int main(int argc, char** argv) {
    // set the device to use
    cudaSetDevice(0);

    uint32_t N = atoi(argv[1]);
    uint32_t K = atoi(argv[2]);


    sample* sx = (sample*)malloc(N * sizeof(sample));
    cluster* cx = (cluster*)malloc(K * sizeof(cluster));

    // Wouldn't it be hillarious if this was the bottleneck?
    // Whether or not it is, it's required by the assignment.
    generate_samples(sx, cx, N, K);

    // get current time
    clock_t start = clock();

    uint32_t iters = k_means_cuda(sx, cx, N, K);

    // elapsed time
    clock_t elapsed = clock() - start;

    // Print the results
    printf("N = %d, K = %d\n", N, K);
    for (uint32_t i = 0; i < K; i++) {
        printf("Center: (%.3f, %.3f) : Size: %d\n",
            cx[i].x, cx[i].y, cx[i]._c);
    }
    printf("Iterations: %d\n", iters);

    // print the time
    printf("Time: %f\n", (float)elapsed / CLOCKS_PER_SEC);

    free(sx);
    free(cx);
}