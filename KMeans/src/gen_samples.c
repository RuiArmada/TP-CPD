#include "../include/gen_samples.h"
#include "../include/common/point.h"

#include <omp.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Generates a set of random points, sequentially.
 *
 * @param samples
 * @param clusters
 * @param cluster_count
 * @param sample_count
 */
void gen_sample_seq(point* samples, point* clusters, uint32_t cluster_count, uint32_t sample_count) {
    srand(10);

    // printf("Generating %d samples and %d clusters\n", sample_count, cluster_count);

    for (uint_fast32_t i = 0; i < sample_count; i += 1) {
        samples[i].x = (float)rand() / RAND_MAX;
        samples[i].y = (float)rand() / RAND_MAX;
    }

    memcpy(clusters, samples, cluster_count * sizeof(point));
}

/**
 * @brief Generates a set of random points, in parallel, using pragma omp parallel for (OpenMP).
 *
 * @param samples
 * @param clusters
 * @param cluster_count
 * @param sample_count
 */
void gen_samples_par(point* samples, point* clusters, uint32_t cluster_count, uint32_t sample_count) {
    srand(10);

    #pragma omp parallel for
    for (uint_fast32_t i = 0; i < sample_count; i += 1) {
        samples[i].x = (float)rand() / RAND_MAX;
        samples[i].y = (float)rand() / RAND_MAX;
    }

    memcpy(clusters, samples, cluster_count * sizeof(point));
}
