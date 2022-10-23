#include "../include/kmeans.h"

#include <immintrin.h>
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
inline void cluster_points(point*, point*, metric*);                          // cluster points to the nearest cluster
inline void cluster_points_2x(point* samples, point* clusters, metric* new);  // cluster points to the nearest cluster, loop unrolled 2x
inline void cluster_points_4x(point* samples, point* clusters, metric* new);  // cluster points to the nearest cluster, loop unrolled 4x
void cluster_points_8x(point* samples, point* clusters, metric* new);         // cluster points to the nearest cluster, loop unrolled 8x
inline bool has_converged(metric*, metric*);                                  // check whether the algorithm has converged
inline int has_converged_branchless(metric* old, metric* new);                // check whether the algorithm has converged (branchless)
k_means_out k_means(point*, point*);

// Original python code was taken from https://datasciencelab.wordpress.com/tag/lloyds-algorithm/

inline void recalculate_centroids(point* clusters, metric* metrics) {
    for (int i = 0; i < K; i++) {
        clusters[i].x = metrics[i].x_sum / metrics[i].total;
        clusters[i].y = metrics[i].y_sum / metrics[i].total;
    }
}

void cluster_points_4x(point* samples, point* clusters, metric* new) {
    for (int i = 0; i < N; i += 4) {
        float min_dist_0 = euclidean_distance(&samples[i], &clusters[0]);
        float min_dist_1 = euclidean_distance(&samples[i + 1], &clusters[0]);
        float min_dist_2 = euclidean_distance(&samples[i + 2], &clusters[0]);
        float min_dist_3 = euclidean_distance(&samples[i + 3], &clusters[0]);

        int cluster_id_0 = 0;
        int cluster_id_1 = 0;
        int cluster_id_2 = 0;
        int cluster_id_3 = 0;

        for (int j = 1; j < K; j++) {
            float d = euclidean_distance(&samples[i], &clusters[j]);
            if (d < min_dist_0) {
                min_dist_0 = d;
                cluster_id_0 = j;
            }

            d = euclidean_distance(&samples[i + 1], &clusters[j]);
            if (d < min_dist_1) {
                min_dist_1 = d;
                cluster_id_1 = j;
            }

            d = euclidean_distance(&samples[i + 2], &clusters[j]);
            if (d < min_dist_2) {
                min_dist_2 = d;
                cluster_id_2 = j;
            }

            d = euclidean_distance(&samples[i + 3], &clusters[j]);
            if (d < min_dist_3) {
                min_dist_3 = d;
                cluster_id_3 = j;
            }
        }

        new[cluster_id_0].x_sum += samples[i].x;
        new[cluster_id_0].y_sum += samples[i].y;
        new[cluster_id_0].total++;

        new[cluster_id_1].x_sum += samples[i + 1].x;
        new[cluster_id_1].y_sum += samples[i + 1].y;
        new[cluster_id_1].total++;

        new[cluster_id_2].x_sum += samples[i + 2].x;
        new[cluster_id_2].y_sum += samples[i + 2].y;
        new[cluster_id_2].total++;

        new[cluster_id_3].x_sum += samples[i + 3].x;
        new[cluster_id_3].y_sum += samples[i + 3].y;
        new[cluster_id_3].total++;
    }

    for (int i = N - (N % 4); i < N; i++) {
        float min_dist = euclidean_distance(&samples[i], &clusters[0]);
        int cluster_id = 0;

        for (int j = 1; j < K; j++) {
            float d = euclidean_distance(&samples[i], &clusters[j]);
            if (d < min_dist) {
                min_dist = d;
                cluster_id = j;
            }
        }

        new[cluster_id].x_sum += samples[i].x;
        new[cluster_id].y_sum += samples[i].y;
        new[cluster_id].total++;
    }
}

void cluster_points_8x(point* samples, point* clusters, metric* new) {
    for (int i = 0; i < N; i += 8) {
        float min_dist_0 = euclidean_distance(&samples[i], &clusters[0]);
        float min_dist_1 = euclidean_distance(&samples[i + 1], &clusters[0]);
        float min_dist_2 = euclidean_distance(&samples[i + 2], &clusters[0]);
        float min_dist_3 = euclidean_distance(&samples[i + 3], &clusters[0]);
        float min_dist_4 = euclidean_distance(&samples[i + 4], &clusters[0]);
        float min_dist_5 = euclidean_distance(&samples[i + 5], &clusters[0]);
        float min_dist_6 = euclidean_distance(&samples[i + 6], &clusters[0]);
        float min_dist_7 = euclidean_distance(&samples[i + 7], &clusters[0]);

        int cluster_id_0 = 0;
        int cluster_id_1 = 0;
        int cluster_id_2 = 0;
        int cluster_id_3 = 0;
        int cluster_id_4 = 0;
        int cluster_id_5 = 0;
        int cluster_id_6 = 0;
        int cluster_id_7 = 0;

        for (int j = 1; j < K; j++) {
            float d = euclidean_distance(&samples[i], &clusters[j]);
            if (d < min_dist_0) {
                min_dist_0 = d;
                cluster_id_0 = j;
            }

            d = euclidean_distance(&samples[i + 1], &clusters[j]);
            if (d < min_dist_1) {
                min_dist_1 = d;
                cluster_id_1 = j;
            }

            d = euclidean_distance(&samples[i + 2], &clusters[j]);
            if (d < min_dist_2) {
                min_dist_2 = d;
                cluster_id_2 = j;
            }

            d = euclidean_distance(&samples[i + 3], &clusters[j]);
            if (d < min_dist_3) {
                min_dist_3 = d;
                cluster_id_3 = j;
            }

            d = euclidean_distance(&samples[i + 4], &clusters[j]);
            if (d < min_dist_4) {
                min_dist_4 = d;
                cluster_id_4 = j;
            }

            d = euclidean_distance(&samples[i + 5], &clusters[j]);
            if (d < min_dist_5) {
                min_dist_5 = d;
                cluster_id_5 = j;
            }

            d = euclidean_distance(&samples[i + 6], &clusters[j]);
            if (d < min_dist_6) {
                min_dist_6 = d;
                cluster_id_6 = j;
            }

            d = euclidean_distance(&samples[i + 7], &clusters[j]);
            if (d < min_dist_7) {
                min_dist_7 = d;
                cluster_id_7 = j;
            }
        }

        new[cluster_id_0].x_sum += samples[i].x;
        new[cluster_id_0].y_sum += samples[i].y;
        new[cluster_id_0].total++;

        new[cluster_id_1].x_sum += samples[i + 1].x;
        new[cluster_id_1].y_sum += samples[i + 1].y;
        new[cluster_id_1].total++;

        new[cluster_id_2].x_sum += samples[i + 2].x;
        new[cluster_id_2].y_sum += samples[i + 2].y;
        new[cluster_id_2].total++;

        new[cluster_id_3].x_sum += samples[i + 3].x;
        new[cluster_id_3].y_sum += samples[i + 3].y;
        new[cluster_id_3].total++;

        new[cluster_id_4].x_sum += samples[i + 4].x;
        new[cluster_id_4].y_sum += samples[i + 4].y;
        new[cluster_id_4].total++;

        new[cluster_id_5].x_sum += samples[i + 5].x;
        new[cluster_id_5].y_sum += samples[i + 5].y;
        new[cluster_id_5].total++;

        new[cluster_id_6].x_sum += samples[i + 6].x;
        new[cluster_id_6].y_sum += samples[i + 6].y;
        new[cluster_id_6].total++;

        new[cluster_id_7].x_sum += samples[i + 7].x;
        new[cluster_id_7].y_sum += samples[i + 7].y;
        new[cluster_id_7].total++;
    }

    for (int i = N - (N % 8); i < N; i++) {
        float min_dist = euclidean_distance(&samples[i], &clusters[0]);
        int cluster_id = 0;

        for (int j = 1; j < K; j++) {
            float d = euclidean_distance(&samples[i], &clusters[j]);
            if (d < min_dist) {
                min_dist = d;
                cluster_id = j;
            }
        }

        new[cluster_id].x_sum += samples[i].x;
        new[cluster_id].y_sum += samples[i].y;
        new[cluster_id].total++;
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
void cluster_points_2x(point* samples, point* clusters, metric* new) {
    for (int i = 0; i < N; i += 2) {
        float min_dist_0 = euclidean_distance(&samples[i], &clusters[0]);
        float min_dist_1 = euclidean_distance(&samples[i + 1], &clusters[0]);

        int cluster_id_0 = 0;
        int cluster_id_1 = 0;

        for (int j = 1; j < K; j++) {
            float d = euclidean_distance(&samples[i], &clusters[j]);

            if (samples[i].d < min_dist_0) {
                min_dist_0 = d;
                cluster_id_0 = j;
            }

            d = euclidean_distance(&samples[i + 1], &clusters[j]);

            if (samples[i + 1].d < min_dist_1) {
                min_dist_1 = d;
                cluster_id_1 = j;
            }
        }

        new[cluster_id_0].x_sum += samples[i].x;
        new[cluster_id_0].y_sum += samples[i].y;
        new[cluster_id_0].total++;

        new[cluster_id_1].x_sum += samples[i + 1].x;
        new[cluster_id_1].y_sum += samples[i + 1].y;
        new[cluster_id_1].total++;
    }

    for (int i = N - (N % 2); i < N; i++) {
        float min_dist = euclidean_distance(&samples[i], &clusters[0]);
        int cluster_id = 0;

        for (int j = 1; j < K; j++) {
            float d = euclidean_distance(&samples[i], &clusters[j]);
            if (d < min_dist) {
                min_dist = d;
                cluster_id = j;
            }
        }

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
void cluster_points(point* samples, point* clusters, metric* new) {
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
k_means_out k_means(point* samples, point* clusters) {
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

    k_means_out out = {.iterations = iter};

    // fill the output struct
    for (int i = 0; i < K; i++) {
        out.sizes[i] = new[i].total;
    }

    // Free the allocated memory
    free(old);
    free(new);

    return out;
}
