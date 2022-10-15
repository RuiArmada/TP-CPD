#include "../include/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Generates a random number between 0 and 255 for each
 *        of the matrix's elements. Step 1a
 *
 * @param samples The matrix to be filled with random values.
 * @param n_samples Size of the matrix (rows and columns).
 */
void gen_samples(point* samples, point* clusters, int n_samples, int n_clusters) {
    // TODO: Ask whether we want a fixed seed or not (for testing purposes)
    srand(time(NULL));

    // Generate random samples
    for (int i = 0; i < n_samples; i++) {
        samples[i].x = (float)rand() / (float)RAND_MAX;
        samples[i].y = (float)rand() / (float)RAND_MAX;
    }

    // Generate random clusters
    for (int i = 0; i < n_clusters; i++) {
        clusters[i].x = samples[i].x;
        clusters[i].y = samples[i].y;
    }
}
