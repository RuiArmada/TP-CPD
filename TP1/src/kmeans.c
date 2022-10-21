#include "../include/kmeans.h"

#include <stdbool.h>
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

void cluster_points(point*, point*, metric*);
inline bool has_converged(int, float, float);
int k_means(point*, point*);

// Original python code was taken from https://datasciencelab.wordpress.com/tag/lloyds-algorithm/

/*
def cluster_points(X, mu):
    clusters  = {}
    for x in X:
        bestmukey = min([(i[0], np.linalg.norm(x-mu[i[0]])) \
                    for i in enumerate(mu)], key=lambda t:t[1])[0]
        try:
            clusters[bestmukey].append(x)
        except KeyError:
            clusters[bestmukey] = [x]
    return clusters
*/
void cluster_points(point* points, point* clusters, metric* metrics) {
}

/**
 * @brief Checks if the algorithm has converged.
 *        Returns true if the algorithm has converged.
 *
 * @param iter Iteration number
 * @param metric Current metric
 * @param old_metric Previous metric
 */
inline bool has_converged(int iter, float old_metric, float metric) {
    return iter > 100 || old_metric > metric;
}

/**
 * @brief Checks whether the algorithm has converged.
 *
 */
inline bool has_converged_new(metric* old, metric* new) {
    for (int i = 0; i < K; i++)
        if (old[i].x_sum != new[i].x_sum || old[i].y_sum != new[i].y_sum || old[i].total != new[i].total)
            return false;
}

// Convergence fun 3, eletric boogaloo
inline bool has_converged_dists(float old, float new) {
    return (old - new) / old < 0.001;
}

/**
 * @brief Assigns each sample to the nearest cluster using the euclidean distance.
 *
 * @param samples
 * @param clusters
 * @param new list of metrics used for the iteration
 */
void assign_samples_to_clusters(point* samples, point* clusters, metric* new) {
    float min_distance, distance;
    int min_cluster_id;

    for (int i = 0; i < N; i++) {
        min_distance = euclidean_distance(&samples[i], &clusters[0]);
        min_cluster_id = 0;

        for (int j = 1; j < K; j++) {
            distance = euclidean_distance(&samples[i], &clusters[j]);
            if (distance < min_distance) {
                min_distance = distance;
                min_cluster_id = j;
            }
        }

        samples[i].id = min_cluster_id;
    }
}

/**
 * @brief K-means algorithm naive implementation.
 *
 * @param samples
 * @param clusters
 */
int k_means(point* samples, point* clusters) {
    int iter = 0;               // itertation counter
    int old_metric, metri = 0;  // metrics to check whether the algorithm has converged

    metric* old = calloc(K, sizeof(metric));
    metric* new = calloc(K, sizeof(metric));

    // Step 1c - Assign each sample to the nearest cluster using the euclidean distance
    assign_samples_to_clusters(samples, clusters, new);

    do {
        // memcpy new to old
        memcpy(old, new, K * sizeof(metric));
        memset(new, 0, K * sizeof(metric));

        // Step 2
        // clusters = cluster_points(X, mu)

        // Step 3
        assign_samples_to_clusters(samples, clusters, new);

        iter++;
    } while (!has_converged(iter, old_metric, metri));  // Step 4, TODO: improve convergence check?

    // Free the allocated memory
    free(old);
    free(new);

    return iter;
}
