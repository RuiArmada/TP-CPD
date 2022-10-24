#include "../include/utils.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void gen_samples(point* samples, point* clusters, int n_samples, int n_clusters) {
    srand(10);  // For reproducibility

    // Step 1a - Initialize a vector with random values (N samples in the (x,y) space)
    for (int i = 0; i < n_samples; i++) {
        samples[i].x = (float)rand() / RAND_MAX;  // x coord
        samples[i].y = (float)rand() / RAND_MAX;  // y coord
    }

    // Step 1b - Initialize the K clusters with the coordinates of the first K samples
    // The first K samples are the initial centroids for reproducibility
    // otherwise, would've been random
    // for (int i = 0; i < n_clusters; i++) {
    //     clusters[i].x = samples[i].x;
    //     clusters[i].y = samples[i].y;
    // }
    // memcpy is faster than the for loop?
    memcpy(clusters, samples, n_clusters * sizeof(point));
}

float euclidean_distance(point* p1, point* p2) {
    return (p1->x - p2->x) * (p1->x - p2->x) + (p1->y - p2->y) * (p1->y - p2->y);
}
