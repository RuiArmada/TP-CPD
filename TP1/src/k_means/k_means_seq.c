#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/common/builtins.h"
#include "../../include/k_means.h"
#include "../../include/euclidean_distance.h"

/**
 * @brief Auxiliary struct to calculate cluster centers
 *       and total number of points in each cluster in
 *       each iteration of the algorithm.
 */
typedef struct {
    float x_sum;  // sum of the x coordinates of the points in the cluster
    float y_sum;  // sum of the y coordinates of the points in the cluster
    int total;    // number of points in the cluster
} metric;

void k_means_seq_recalc_clusters(point* samples, const metric* clusters, const uint32_t cluster_count);
void cluster_points_seq(const point* samples, const point* clusters, metric* new, const uint32_t sample_count, const uint32_t cluster_count);
uint32_t k_means_seq_has_converged(const metric* old, const metric* new, const uint32_t cluster_count);

// Original python code was taken from https://datasciencelab.wordpress.com/tag/lloyds-algorithm/

void k_means_seq_recalc_clusters(point* clusters, const metric* metrics, const uint32_t cluster_count) {
    for (uint32_t i = 0; i < cluster_count; i++) {
        clusters[i].x = metrics[i].x_sum / metrics[i].total;
        clusters[i].y = metrics[i].y_sum / metrics[i].total;
    }
}

/**
 * @brief Cluster points implementations.
 *
 * @param samples
 * @param clusters
 * @param new
 */
 // cluster points
void cluster_points_seq(const point* samples, const point* clusters, metric* new, const uint32_t sample_count, const uint32_t cluster_count) {
    for (uint32_t i = 0; i < sample_count; i++) {
        float min_distance = euclidean_distance_squared(&samples[i], &clusters[0]);
        int cluster_id = 0;
        for (uint32_t j = 1; j < cluster_count; j++) {
            float distance = euclidean_distance_squared(&samples[i], &clusters[j]);
            if (distance < min_distance) {
                min_distance = distance;
                cluster_id = j;
            }
        }

        new[cluster_id].x_sum += samples[i].x;
        new[cluster_id].y_sum += samples[i].y;
        new[cluster_id].total++;
    }
}

/**
 * @brief Checks whether the algorithm has converged.
 *
 * @param old metric struct with previous iter values.
 * @param new metric struct with current iter values.
 */
uint32_t k_means_seq_has_converged(const metric* old, const metric* new, const uint32_t cluster_count) {
    uint32_t counter = 0;
    for (uint32_t i = 0; i < cluster_count; i++) {
        counter |= (old[i].x_sum != new[i].x_sum) | (old[i].y_sum != new[i].y_sum) | (old[i].total != new[i].total);
    }
    return counter;
}

/**
 * @brief K-means algorithm naive implementation.
 *
 * @param samples
 * @param clusters
 */
k_means_out k_means_seq(const point* samples, point* clusters, const uint32_t sample_count, const uint32_t cluster_count) {
    int iter = 0;  // iteration counter

    metric* old = calloc(cluster_count, sizeof(metric));
    metric* new = calloc(cluster_count, sizeof(metric));

    // Step 1c - Assign each sample to the nearest cluster using the euclidean distance.
    cluster_points_seq(samples, clusters, new, sample_count, cluster_count);

    do {
        // Step 2 - Calculate the centroid of each cluster. (also known as the geometric center)
        k_means_seq_recalc_clusters(clusters, new, cluster_count);

        // Delete previous iter's metrics: set "new" to "old" and "new" to 0
        memcpy(old, new, cluster_count * sizeof(metric));
        memset(new, 0, cluster_count * sizeof(metric));

        // Step 3 - Assign each sample to the nearest cluster using the euclidean distance
        cluster_points_seq(samples, clusters, new, sample_count, cluster_count);

        iter++;
    } while (k_means_seq_has_converged(old, new, cluster_count));  // Step 4, TODO: improve convergence check?

    k_means_out out = { .iterations = iter };

    // fill the output struct
    for (uint32_t i = 0; i < cluster_count; i++) {
        out.cluster_size[i] = new[i].total;
    }

    // Free the allocated memory
    free(old);
    free(new);

    return out;
}
