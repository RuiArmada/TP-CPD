#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/kmeans.h"
#include "../include/utils.h"

// Steps as described in the assignment
// Step 1 - Initialize the samples & clusters.
// Step 1a - Initialize a vector with random values. (N samples in the (x,y) space)
// Step 1b - Initialize the K clusters with the coordinates of the first K samples.
// Step 1c - Assign each sample to the nearest cluster using the euclidean distance.
// Step 2 - Calculate the centroid of each cluster. (also known as geometric center)
// Step 3 - Assign each sample to the nearest cluster using the euclidean distance.
// Step 4 - Repeat steps 2 and 3 until there are no points that change clusters.

int main() {
    point* samples = malloc(N * sizeof(point));
    point* clusters = malloc(K * sizeof(point));

    if (samples == NULL || clusters == NULL) {
        printf("Error allocating memory for samples or clusters. Exiting...");
        return EXIT_FAILURE;
    }
    // Step 1a, 1b
    gen_samples(samples, clusters);

    // Step 1c, 2, 3, 4
    k_means_out out = k_means(samples, clusters);

    // Print the results
    printf("N = %d, K = %d\n", N, K);
    for (int i = 0; i < K; i++) {
        printf("Center: (%.3f, %.3f) : Size: %d\n",
               clusters[i].x, clusters[i].y, out.sizes[i]);
    }
    printf("Iterations: %d\n", out.iterations);

    // free(samples);
    // free(clusters);

    return EXIT_SUCCESS;
}