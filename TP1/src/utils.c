#include "../include/utils.h"

#include <immintrin.h>
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/bconsts.h"

void gen_samples(point* samples, point* clusters) {
    srand(10);  // For reproducibility

    // Step 1a - Initialize a vector with random values (N samples in the (x,y) space)
    for (int i = 0; i < N; i += 1) {
        samples[i].x = (float)rand() / RAND_MAX;
        samples[i].y = (float)rand() / RAND_MAX;
    }

    // Step 1b - Initialize the K clusters with the coordinates of the first K samples
    // The first K samples are the initial centroids for reproducibility
    // otherwise, would've been random
    // for (int i = 0; i < n_clusters; i++) {
    //     clusters[i].x = samples[i].x;
    //     clusters[i].y = samples[i].y;
    // }
    memcpy(clusters, samples, K * sizeof(point));
}

#if EUCLIDEAN_FUNC == 1
float euclidean_distance(const point* p1, const point* p2) { return sqrt((p1->x - p2->x) * (p1->x - p2->x) + (p1->y - p2->y) * (p1->y - p2->y)); }
#elif EUCLIDEAN_FUNC == 2
float euclidean_distance(const point* p1, const point* p2) { return (p1->x - p2->x) * (p1->x - p2->x) + (p1->y - p2->y) * (p1->y - p2->y); }
#elif EUCLIDEAN_FUNC == 3
#pragma omp declare simd simdlen(K)
float euclidean_distance(const point* p1, const point* p2) { return (p1->x - p2->x) * (p1->x - p2->x) + (p1->y - p2->y) * (p1->y - p2->y); }
#endif
