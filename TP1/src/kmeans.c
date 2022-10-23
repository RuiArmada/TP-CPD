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
int k_means(point*, point*);

// Original python code was taken from https://datasciencelab.wordpress.com/tag/lloyds-algorithm/

inline void recalculate_centroids(point* clusters, metric* metrics) {
    for (int i = 0; i < K; i++) {
        clusters[i].x = metrics[i].x_sum / metrics[i].total;
        clusters[i].y = metrics[i].y_sum / metrics[i].total;
        clusters[i].id = metrics[i].total;
    }
}

inline void cluster_points_8x(point* samples, point* clusters, metric* new) {
    for (int i = 0; i < N; i += 8) {
        for (int j = 0; j < K; j++) {
            float d1 = euclidean_distance(&samples[i], &clusters[j]);
            float d2 = euclidean_distance(&samples[i + 1], &clusters[j]);
            float d3 = euclidean_distance(&samples[i + 2], &clusters[j]);
            float d4 = euclidean_distance(&samples[i + 3], &clusters[j]);
            float d5 = euclidean_distance(&samples[i + 4], &clusters[j]);
            float d6 = euclidean_distance(&samples[i + 5], &clusters[j]);
            float d7 = euclidean_distance(&samples[i + 6], &clusters[j]);
            float d8 = euclidean_distance(&samples[i + 7], &clusters[j]);

            if (d1 < samples[i].d) {
                samples[i].d = d1;
                samples[i].id = j;
            }
            if (d2 < samples[i + 1].d) {
                samples[i + 1].d = d2;
                samples[i + 1].id = j;
            }
            if (d3 < samples[i + 2].d) {
                samples[i + 2].d = d3;
                samples[i + 2].id = j;
            }
            if (d4 < samples[i + 3].d) {
                samples[i + 3].d = d4;
                samples[i + 3].id = j;
            }
            if (d5 < samples[i + 4].d) {
                samples[i + 4].d = d5;
                samples[i + 4].id = j;
            }
            if (d6 < samples[i + 5].d) {
                samples[i + 5].d = d6;
                samples[i + 5].id = j;
            }
            if (d7 < samples[i + 6].d) {
                samples[i + 6].d = d7;
                samples[i + 6].id = j;
            }
            if (d8 < samples[i + 7].d) {
                samples[i + 7].d = d8;
                samples[i + 7].id = j;
            }
        }

        new[samples[i].id].x_sum += samples[i].x;
        new[samples[i].id].y_sum += samples[i].y;
        new[samples[i].id].total++;

        new[samples[i + 1].id].x_sum += samples[i + 1].x;
        new[samples[i + 1].id].y_sum += samples[i + 1].y;
        new[samples[i + 1].id].total++;

        new[samples[i + 2].id].x_sum += samples[i + 2].x;
        new[samples[i + 2].id].y_sum += samples[i + 2].y;
        new[samples[i + 2].id].total++;

        new[samples[i + 3].id].x_sum += samples[i + 3].x;
        new[samples[i + 3].id].y_sum += samples[i + 3].y;
        new[samples[i + 3].id].total++;

        new[samples[i + 4].id].x_sum += samples[i + 4].x;
        new[samples[i + 4].id].y_sum += samples[i + 4].y;
        new[samples[i + 4].id].total++;

        new[samples[i + 5].id].x_sum += samples[i + 5].x;
        new[samples[i + 5].id].y_sum += samples[i + 5].y;
        new[samples[i + 5].id].total++;

        new[samples[i + 6].id].x_sum += samples[i + 6].x;
        new[samples[i + 6].id].y_sum += samples[i + 6].y;
        new[samples[i + 6].id].total++;

        new[samples[i + 7].id].x_sum += samples[i + 7].x;
        new[samples[i + 7].id].y_sum += samples[i + 7].y;
        new[samples[i + 7].id].total++;
    }

    for (int i = N - (N % 8); i < N; i++) {
        for (int j = 0; j < K; j++) {
            float d = euclidean_distance(&samples[i], &clusters[j]);

            if (d < samples[i].d) {
                samples[i].d = d;
                samples[i].id = j;
            }
        }

        // update the metrics
        new[samples[i].id].x_sum += samples[i].x;
        new[samples[i].id].y_sum += samples[i].y;
        new[samples[i].id].total++;
    }
}

inline void cluster_points_4x(point* samples, point* clusters, metric* new) {
    for (int i = 0; i < N; i += 4) {
        // iterate over the clusters
        for (int j = 0; j < K; j++) {
            // calculate the distance between the sample and the cluster
            float d1 = euclidean_distance(&samples[i], &clusters[j]);
            float d2 = euclidean_distance(&samples[i + 1], &clusters[j]);
            float d3 = euclidean_distance(&samples[i + 2], &clusters[j]);
            float d4 = euclidean_distance(&samples[i + 3], &clusters[j]);

            // assign the sample to the nearest cluster
            if (d1 < samples[i].d) {
                samples[i].d = d1;
                samples[i].id = j;
            }
            if (d2 < samples[i + 1].d) {
                samples[i + 1].d = d2;
                samples[i + 1].id = j;
            }
            if (d3 < samples[i + 2].d) {
                samples[i + 2].d = d3;
                samples[i + 2].id = j;
            }
            if (d4 < samples[i + 3].d) {
                samples[i + 3].d = d4;
                samples[i + 3].id = j;
            }
        }

        // update the metrics
        new[samples[i].id].x_sum += samples[i].x;
        new[samples[i].id].y_sum += samples[i].y;
        new[samples[i].id].total++;

        new[samples[i + 1].id].x_sum += samples[i + 1].x;
        new[samples[i + 1].id].y_sum += samples[i + 1].y;
        new[samples[i + 1].id].total++;

        new[samples[i + 2].id].x_sum += samples[i + 2].x;
        new[samples[i + 2].id].y_sum += samples[i + 2].y;
        new[samples[i + 2].id].total++;

        new[samples[i + 3].id].x_sum += samples[i + 3].x;
        new[samples[i + 3].id].y_sum += samples[i + 3].y;
        new[samples[i + 3].id].total++;
    }

    for (int i = N - (N % 4); i < N; i++) {
        // iterate over the clusters
        for (int j = 0; j < K; j++) {
            // calculate the distance between the sample and the cluster
            float d = euclidean_distance(&samples[i], &clusters[j]);

            // assign the sample to the nearest cluster
            if (d < samples[i].d) {
                samples[i].d = d;
                samples[i].id = j;
            }
        }

        // update the metrics
        new[samples[i].id].x_sum += samples[i].x;
        new[samples[i].id].y_sum += samples[i].y;
        new[samples[i].id].total++;
    }
}

/**
 * @brief Assign each sample to the nearest cluster using the euclidean distance.
 *        This version of the algorithm loops two items at a time.
 *
 * @param samples
 * @param clusters
 * @param new
 */
inline void cluster_points_2x(point* samples, point* clusters, metric* new) {
    for (int i = 0; i < N; i += 2) {
        float min_dist_0 = euclidean_distance(&samples[i], &clusters[0]);
        float min_dist_1 = euclidean_distance(&samples[i + 1], &clusters[0]);

        int cluster_id_0 = 0;
        int cluster_id_1 = 0;

        for (int j = 0; j < K; j++) {
            samples[i].d = euclidean_distance(&samples[i], &clusters[j]);

            if (samples[i].d < min_dist_0) {
                min_dist_0 = samples[i].d;
                cluster_id_0 = j;
            }

            samples[i + 1].d = euclidean_distance(&samples[i + 1], &clusters[j]);

            if (samples[i + 1].d < min_dist_1) {
                min_dist_1 = samples[i + 1].d;
                cluster_id_1 = j;
            }
        }

        samples[i].id = cluster_id_0;
        samples[i + 1].id = cluster_id_1;

        new[cluster_id_0].x_sum += samples[i].x;
        new[cluster_id_0].y_sum += samples[i].y;
        new[cluster_id_0].total++;

        new[cluster_id_1].x_sum += samples[i + 1].x;
        new[cluster_id_1].y_sum += samples[i + 1].y;
        new[cluster_id_1].total++;
    }

    // If N is odd, the last sample is not processed in the loop above
    if (N % 2) {
        int i = N - 1;
        float min_dist = euclidean_distance(&samples[i], &clusters[0]);
        int cluster_id = 0;

        for (int j = 0; j < K; j++) {
            samples[i].d = euclidean_distance(&samples[i], &clusters[j]);

            if (samples[i].d < min_dist) {
                min_dist = samples[i].d;
                cluster_id = j;
            }
        }

        samples[i].id = cluster_id;

        new[cluster_id].x_sum += samples[i].x;
        new[cluster_id].y_sum += samples[i].y;
        new[cluster_id].total++;
    }
}

/**
 * @brief Assigns each sample to the nearest cluster using the euclidean distance.
 *
 * @param samples
 * @param clusters
 * @param new list of metrics used for the iteration
 */
inline void cluster_points(point* samples, point* clusters, metric* new) {
    for (int i = 0; i < N; i++) {
        float min_distance = euclidean_distance(&samples[i], &clusters[0]);
        int cluster_id = 0;

        for (int j = 1; j < K; j++) {
            float distance = euclidean_distance(&samples[i], &clusters[j]);
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

inline bool has_converged(metric* old, metric* new) {
    for (int i = 0; i < K; i++) {
        if (old[i].x_sum != new[i].x_sum || old[i].y_sum != new[i].y_sum || old[i].total != new[i].total) {
            return false;
        }
    }
    return true;
}

inline int has_converged_branchless(metric* old, metric* new) {
    int i = 0;

    int val = old[i].x_sum != new[i].x_sum || old[i].y_sum != new[i].y_sum || old[i].total != new[i].total;

    for (i = 1; i < K; i++) {
        val |= (old[i].x_sum != new[i].x_sum || old[i].y_sum != new[i].y_sum || old[i].total != new[i].total);
    }

    return val;
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
        cluster_points_4x(samples, clusters, new);

        iter++;
        //} while (has_converged_branchless(old, new));  // Step 4, TODO: improve convergence check?
    } while (!has_converged(old, new));  // Step 4, TODO: improve convergence check?

    // Free the allocated memory
    free(old);
    free(new);

    return iter;
}
