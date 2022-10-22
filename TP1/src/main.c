#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/kmeans.h"
#include "../include/logging.h"
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
    printf("Allocating memory for samples and clusters.\n");
    point* samples = malloc(N * sizeof(point));
    point* clusters = malloc(K * sizeof(point));
    char* filename = calloc(30, sizeof(char));

    if (samples == NULL || clusters == NULL) {
        printf("Error allocating memory for samples or clusters. Exiting...");
        return EXIT_FAILURE;
    }

    if (filename == NULL) {
        printf("Error allocating memory for filename. Exiting...");
        return EXIT_FAILURE;
    }

    generate_filename(filename);
    FILE* file = generate_file(filename);

    // Step 1a, 1b
    gen_samples(samples, clusters, N, K);
    // Step 1c, 2, 3, 4
    int iter = k_means(samples, clusters);

    log_message_to_console(K, N, iter, clusters);
    log_message_to_file(file, K, N, iter, clusters);

    printf("Cleaning up...\n");
    free(samples);
    free(clusters);
    free(filename);
    fclose(file);
    printf("Done!\n");

    return EXIT_SUCCESS;
}