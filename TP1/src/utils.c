#include "../include/utils.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gen_samples(point* samples, point* clusters, int n_samples, int n_clusters) {
    srand(10);  // For reproducibility

    // Step 1a - Initialize a vector with random values (N samples in the (x,y) space)
    for (int i = 0; i < n_samples; i++) {
        samples[i].id = -1;                       // -1 means that the sample is not assigned to any cluster
        samples[i].x = (float)rand() / RAND_MAX;  // x coord
        samples[i].y = (float)rand() / RAND_MAX;  // y coord
        samples[i].d = __FLT_MAX__;               // distance to the cluster, init'd to "infinity"
    }

    // Step 1b - Initialize the K clusters with the coordinates of the first K samples
    // According to the algorithm, these should be random samples.
    // However, for the sake of reproducibility, the first K samples are used.
    for (int i = 0; i < n_clusters; i++) {
        clusters[i].x = samples[i].x;
        clusters[i].y = samples[i].y;
        clusters[i].id = 0.0;
        clusters[i].d = __FLT_MAX__;
        // clusters->points = NULL;  // TODO: allocate memory for the points
    }

    // Step 1c - Assign each sample to the nearest cluster using the euclidean distance
}

inline float euclidean_distance(point* p1, point* p2) {
    return sqrt(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2));
}
