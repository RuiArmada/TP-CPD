#include "../include/kmeans.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if CLUSTER_FUNC == 9
#include <omp.h>
#endif

#include "../include/bconsts.h"

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

void recalculate_centroids(point* samples, metric* clusters);
void cluster_points(point* samples, point* clusters, metric* new);  // cluster points to the nearest cluster
int has_converged(metric* old, metric* new);                        // check whether the algorithm has converged
k_means_out k_means(point*, point*);

// Original python code was taken from https://datasciencelab.wordpress.com/tag/lloyds-algorithm/

void recalculate_centroids(point* clusters, metric* metrics) {
    for (int i = 0; i < K; i++) {
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
#if CLUSTER_FUNC == 1 || CLUSTER_FUNC == 9
// cluster points
void cluster_points(point* samples, point* clusters, metric* new) {
    for (int i = 0; i < N; i++) {
        float min_distance = euclidean_distance(&samples[i], &clusters[0]);
        int cluster_id = 0;
#if CLUSTER_FUNC == 9
#pragma omp simd
#endif
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

#elif CLUSTER_FUNC == 2
// cluster_points loop unrolled 2x
void cluster_points(point* samples, point* clusters, metric* new) {
    for (int i = 0; i < N; i += 2) {
        float min_dist_0 = euclidean_distance(&samples[i], &clusters[0]);
        float min_dist_1 = euclidean_distance(&samples[i + 1], &clusters[0]);

        int cluster_id_0 = 0;
        int cluster_id_1 = 0;

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

#elif CLUSTER_FUNC == 3
// cluster_points loop unrolled 4x

void cluster_points(point* samples, point* clusters, metric* new) {
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

#elif CLUSTER_FUNC == 4
// cluster_points loop unrolled 8x
void cluster_points(point* samples, point* clusters, metric* new) {
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

#elif CLUSTER_FUNC == 5
// cluster_points loop branchless
void cluster_points(point* samples, point* clusters, metric* new) {
    for (int i = 0; i < N; i++) {
        float min_distance = euclidean_distance(&samples[i], &clusters[0]);
        int cluster_id = 0;

        for (int j = 1; j < K; j++) {
            float distance = euclidean_distance(&samples[i], &clusters[j]);
            int mask = distance < min_distance;
            min_distance = min_distance * (1 - mask) + distance * mask;
            cluster_id = cluster_id * (1 - mask) + j * mask;
        }

        new[cluster_id].x_sum += samples[i].x;
        new[cluster_id].y_sum += samples[i].y;
        new[cluster_id].total++;
    }
}

#elif CLUSTER_FUNC == 6
// cluster_points branchless loop unrolled 2x
void cluster_points(point* samples, point* clusters, metric* new) {
    for (int i = 0; i < N; i += 2) {
        float min_distance_0 = euclidean_distance(&samples[i], &clusters[0]);
        float min_distance_1 = euclidean_distance(&samples[i + 1], &clusters[0]);

        int cluster_id_0 = 0;
        int cluster_id_1 = 0;

        for (int j = 1; j < K; j++) {
            float distance = euclidean_distance(&samples[i], &clusters[j]);
            int mask = distance < min_distance_0;
            min_distance_0 = min_distance_0 * (1 - mask) + distance * mask;
            cluster_id_0 = cluster_id_0 * (1 - mask) + j * mask;

            distance = euclidean_distance(&samples[i + 1], &clusters[j]);
            mask = distance < min_distance_1;
            min_distance_1 = min_distance_1 * (1 - mask) + distance * mask;
            cluster_id_1 = cluster_id_1 * (1 - mask) + j * mask;
        }

        new[cluster_id_0].x_sum += samples[i].x;
        new[cluster_id_0].y_sum += samples[i].y;
        new[cluster_id_0].total++;

        new[cluster_id_1].x_sum += samples[i + 1].x;
        new[cluster_id_1].y_sum += samples[i + 1].y;
        new[cluster_id_1].total++;
    }

    for (int i = N - (N % 2); i < N; i++) {
        float min_distance = euclidean_distance(&samples[i], &clusters[0]);
        int cluster_id = 0;

        for (int j = 1; j < K; j++) {
            float distance = euclidean_distance(&samples[i], &clusters[j]);
            int mask = distance < min_distance;
            min_distance = min_distance * (1 - mask) + distance * mask;
            cluster_id = cluster_id * (1 - mask) + j * mask;
        }

        new[cluster_id].x_sum += samples[i].x;
        new[cluster_id].y_sum += samples[i].y;
        new[cluster_id].total++;
    }
}

#elif CLUSTER_FUNC == 7
// cluster_points branchless loop unrolled 4x
void cluster_points(point* samples, point* clusters, metric* new) {
    for (int i = 0; i < N; i += 4) {
        float min_distance_0 = euclidean_distance(&samples[i], &clusters[0]);
        float min_distance_1 = euclidean_distance(&samples[i + 1], &clusters[0]);
        float min_distance_2 = euclidean_distance(&samples[i + 2], &clusters[0]);
        float min_distance_3 = euclidean_distance(&samples[i + 3], &clusters[0]);

        int cluster_id_0 = 0;
        int cluster_id_1 = 0;
        int cluster_id_2 = 0;
        int cluster_id_3 = 0;

        for (int j = 1; j < K; j++) {
            float distance = euclidean_distance(&samples[i], &clusters[j]);
            int mask = distance < min_distance_0;
            min_distance_0 = min_distance_0 * (1 - mask) + distance * mask;
            cluster_id_0 = cluster_id_0 * (1 - mask) + j * mask;

            distance = euclidean_distance(&samples[i + 1], &clusters[j]);
            mask = distance < min_distance_1;
            min_distance_1 = min_distance_1 * (1 - mask) + distance * mask;
            cluster_id_1 = cluster_id_1 * (1 - mask) + j * mask;

            distance = euclidean_distance(&samples[i + 2], &clusters[j]);
            mask = distance < min_distance_2;
            min_distance_2 = min_distance_2 * (1 - mask) + distance * mask;
            cluster_id_2 = cluster_id_2 * (1 - mask) + j * mask;

            distance = euclidean_distance(&samples[i + 3], &clusters[j]);
            mask = distance < min_distance_3;
            min_distance_3 = min_distance_3 * (1 - mask) + distance * mask;
            cluster_id_3 = cluster_id_3 * (1 - mask) + j * mask;
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
        float min_distance = euclidean_distance(&samples[i], &clusters[0]);
        int cluster_id = 0;

        for (int j = 1; j < K; j++) {
            float distance = euclidean_distance(&samples[i], &clusters[j]);
            int mask = distance < min_distance;
            min_distance = min_distance * (1 - mask) + distance * mask;
            cluster_id = cluster_id * (1 - mask) + j * mask;
        }

        new[cluster_id].x_sum += samples[i].x;
        new[cluster_id].y_sum += samples[i].y;
        new[cluster_id].total++;
    }
}

#elif CLUSTER_FUNC == 8
// cluster_points branchless loop unrolled 8x
void cluster_points(point* samples, point* clusters, metric* new) {
    for (int i = 0; i < N; i += 8) {
        float min_distance_0 = euclidean_distance(&samples[i], &clusters[0]);
        float min_distance_1 = euclidean_distance(&samples[i + 1], &clusters[0]);
        float min_distance_2 = euclidean_distance(&samples[i + 2], &clusters[0]);
        float min_distance_3 = euclidean_distance(&samples[i + 3], &clusters[0]);
        float min_distance_4 = euclidean_distance(&samples[i + 4], &clusters[0]);
        float min_distance_5 = euclidean_distance(&samples[i + 5], &clusters[0]);
        float min_distance_6 = euclidean_distance(&samples[i + 6], &clusters[0]);
        float min_distance_7 = euclidean_distance(&samples[i + 7], &clusters[0]);

        int cluster_id_0 = 0;
        int cluster_id_1 = 0;
        int cluster_id_2 = 0;
        int cluster_id_3 = 0;
        int cluster_id_4 = 0;
        int cluster_id_5 = 0;
        int cluster_id_6 = 0;
        int cluster_id_7 = 0;

        for (int j = 1; j < K; j++) {
            float distance = euclidean_distance(&samples[i], &clusters[j]);
            int mask = distance < min_distance_0;
            min_distance_0 = min_distance_0 * (1 - mask) + distance * mask;
            cluster_id_0 = cluster_id_0 * (1 - mask) + j * mask;

            distance = euclidean_distance(&samples[i + 1], &clusters[j]);
            mask = distance < min_distance_1;
            min_distance_1 = min_distance_1 * (1 - mask) + distance * mask;
            cluster_id_1 = cluster_id_1 * (1 - mask) + j * mask;

            distance = euclidean_distance(&samples[i + 2], &clusters[j]);
            mask = distance < min_distance_2;
            min_distance_2 = min_distance_2 * (1 - mask) + distance * mask;
            cluster_id_2 = cluster_id_2 * (1 - mask) + j * mask;

            distance = euclidean_distance(&samples[i + 3], &clusters[j]);
            mask = distance < min_distance_3;
            min_distance_3 = min_distance_3 * (1 - mask) + distance * mask;
            cluster_id_3 = cluster_id_3 * (1 - mask) + j * mask;

            distance = euclidean_distance(&samples[i + 4], &clusters[j]);
            mask = distance < min_distance_4;
            min_distance_4 = min_distance_4 * (1 - mask) + distance * mask;
            cluster_id_4 = cluster_id_4 * (1 - mask) + j * mask;

            distance = euclidean_distance(&samples[i + 5], &clusters[j]);
            mask = distance < min_distance_5;
            min_distance_5 = min_distance_5 * (1 - mask) + distance * mask;
            cluster_id_5 = cluster_id_5 * (1 - mask) + j * mask;

            distance = euclidean_distance(&samples[i + 6], &clusters[j]);
            mask = distance < min_distance_6;
            min_distance_6 = min_distance_6 * (1 - mask) + distance * mask;
            cluster_id_6 = cluster_id_6 * (1 - mask) + j * mask;

            distance = euclidean_distance(&samples[i + 7], &clusters[j]);
            mask = distance < min_distance_7;
            min_distance_7 = min_distance_7 * (1 - mask) + distance * mask;
            cluster_id_7 = cluster_id_7 * (1 - mask) + j * mask;
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
        float min_distance = euclidean_distance(&samples[i], &clusters[0]);
        int cluster_id = 0;

        for (int j = 1; j < K; j++) {
            float distance = euclidean_distance(&samples[i], &clusters[j]);
            int mask = distance < min_distance;
            min_distance = min_distance * (1 - mask) + distance * mask;
            cluster_id = cluster_id * (1 - mask) + j * mask;
        }

        new[cluster_id].x_sum += samples[i].x;
        new[cluster_id].y_sum += samples[i].y;
        new[cluster_id].total++;
    }
}
#endif

/**
 * @brief Checks whether the algorithm has converged.
 *
 * @param old metric struct with previous iter values.
 * @param new metric struct with current iter values.
 */
inline int has_converged(metric* old, metric* new) {
    int i = 0, counter = 0;
    for (i = 0; i < K; i++) {
        counter |= (old[i].x_sum != new[i].x_sum) | (old[i].y_sum != new[i].y_sum) | (old[i].total != new[i].total);
    }
    return counter;
}
/*
inline int has_converged(metric* old, metric* new) {
    for (int i = 0; i < K; i++) {
        if (old[i].x_sum != new[i].x_sum || old[i].y_sum != new[i].y_sum || old[i].total != new[i].total) {
            return 0;
        }
    }
    return 1;
}
*/

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
        cluster_points(samples, clusters, new);

        iter++;
    } while (has_converged(old, new));  // Step 4, TODO: improve convergence check?

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
