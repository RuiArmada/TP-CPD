#include "../include/kmeans.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

inline void recalculate_centroids(point*, metric*);
void cluster_points(point*, point*, metric*);
inline bool has_converged(metric*, metric*);
inline bool has_converged_dists(float, float);
int k_means(point*, point*);

// Original python code was taken from https://datasciencelab.wordpress.com/tag/lloyds-algorithm/

void recalculate_centroids(point* clusters, metric* metrics) {
    for (int i = 0; i < K; i++) {
        clusters[i].x = metrics[i].x_sum / metrics[i].total;
        clusters[i].y = metrics[i].y_sum / metrics[i].total;
        clusters[i].id = metrics[i].total;
    }
}

/**
 * @brief Assigns each sample to the nearest cluster using the euclidean distance.
 *
 * @param samples
 * @param clusters
 * @param new list of metrics used for the iteration
 */
void cluster_points(point* samples, point* clusters, metric* new) {
    for (int i = 0; i < N; i++) {
        // TODO: use this to avoid one call to euclidean_distance.
        //       Doing so will require some changes elsewhere.
        //       Should yield a small performance boost.
        //       Roughly -20% of the time spent in this function.
        // float min_distance = samples[i].d;
        float min_distance = euclidean_distance(&samples[i], &clusters[0]);
        // float min_distance =
        //     (samples[i].x - clusters[0].x) * (samples[i].x - clusters[0].x) +
        //     (samples[i].y - clusters[0].y) * (samples[i].y - clusters[0].y);
        int cluster_id = 0;

        for (int j = 0; j < K; j++) {
            float distance = euclidean_distance(&samples[i], &clusters[j]);
            // float distance =
            //    (samples[i].x - clusters[j].x) * (samples[i].x - clusters[j].x) +
            //    (samples[i].y - clusters[j].y) * (samples[i].y - clusters[j].y);
            if (distance < min_distance) {
                min_distance = distance;
                cluster_id = j;
            }
        }

        samples[i].id = cluster_id;
        samples[i].d = min_distance;

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

bool has_converged(metric* old, metric* new) {
    for (int i = 0; i < K; i++) {
        if (old[i].x_sum != new[i].x_sum || old[i].y_sum != new[i].y_sum || old[i].total != new[i].total) {
            return false;
        }
    }
    return true;
}

/**
 * @brief
 *
 * @param old total distances of previous iteration.
 * @param new total distances of current iteration.
 */
inline bool has_converged_dists(float old, float new) {
    return (old - new) / old < 0.001;
}

/**
 * @brief K-means algorithm naive implementation.
 *
 * @param samples
 * @param clusters
 */
int k_means(point* samples, point* clusters) {
    int iter = 0;  // itertation counter

    metric* old = calloc(K, sizeof(metric));
    metric* new = calloc(K, sizeof(metric));

    // Step 1c - Assign each sample to the nearest cluster using the euclidean distance.
    cluster_points(samples, clusters, new);

    do {
        // Step 2 - Calculate the centroid of each cluster. (also known as the geometric center)
        recalculate_centroids(clusters, new);

        // Delete previous iter's metrics: set "new" to "old" and "new" to 0
        memcpy(old, new, K * sizeof(metric));
        memset(new, 0, K * sizeof(metric));

        // Step 3 - Assign each sample to the nearest cluster using the euclidean distance
        cluster_points(samples, clusters, new);

        iter++;
    } while (!has_converged(old, new));  // Step 4, TODO: improve convergence check?

    // Free the allocated memory
    free(old);
    free(new);

    return iter;
}
