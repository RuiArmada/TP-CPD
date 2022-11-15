#include <omp.h>
#include <stdio.h>
#include <string.h>


#include "../../include/common/builtins.h"
#include "../../include/k_means.h"
#include "../../include/euclidean_distance.h"

void k_means_par_recalc_clusters(point* clusters, const uint32_t cluster_size, k_means_aux** aux, const uint32_t num_threads);
// uint32_t k_means_par_has_converged(const k_means_aux* old, const k_means_aux* new, const uint32_t cluster_count, const uint32_t iter_count);
void k_means_par_cluster_points(const point* samples, const point* clusters, k_means_aux** new, const uint32_t sample_count, const uint32_t cluster_count, const uint32_t num_threads);

/**
 * @brief This functions folds the auxiliary structs of each thread into a single auxiliary struct.
 *
 * @param acc
 * @param vec
 * @param num_threads
 * @param cluster_count
 */
inline void aux_fold(k_means_aux* acc, k_means_aux** vec, const uint32_t num_threads, const uint32_t cluster_count) {
	// print new
	for (uint32_t i = 0; i < num_threads; i++) {
		for (uint32_t j = 0; j < cluster_count; j++) {
			acc[j].x_sum += vec[i][j].x_sum;
			acc[j].y_sum += vec[i][j].y_sum;
			acc[j].total += vec[i][j].total;
		}
	}
}

/**
 * @brief Recalculates the centroid of each cluster.
 *
 * @param clusters The clusters.
 * @param cluster_size The size of each cluster.
 * @param aux The auxiliary struct containing values of the last iteration.
 */
void k_means_par_recalc_clusters(point* clusters, const uint32_t cluster_count, k_means_aux** aux, const uint32_t num_threads) {
	k_means_aux totals[cluster_count];
	memset(totals, 0, sizeof(k_means_aux) * cluster_count);

	aux_fold(totals, aux, num_threads, cluster_count);

	#pragma omp parallel shared(clusters, totals)
	{
		#pragma omp for schedule(static)
		for (uint32_t i = 0; i < cluster_count; i++) {
			clusters[i].x = totals[i].x_sum / totals[i].total;
			clusters[i].y = totals[i].y_sum / totals[i].total;
		}
	}
}

/**
 * @brief Checks whether the algorithm has converged.
 *
 * @param old metric struct with previous iter values.
 * @param new metric struct with current iter values.
 */
inline uint32_t k_means_par_has_converged(const uint32_t iter) {
	// Due to changes in the assignment, the maximum number of iterations for the parallel version is STOP_CRITERION (default 20).
	return iter < STOP_CRITERION;
}

/**
 * @brief Assigns each point to a cluster.
 *
 * @param samples The points to be clustered.
 * @param clusters The clusters.
 * @param new The auxiliary struct containing values of the current iteration.
 * @param sample_count The number of points.
 * @param cluster_count The number of clusters.
 */
void k_means_par_cluster_points(const point* samples, const point* clusters, k_means_aux** new, const uint32_t sample_count, const uint32_t cluster_count, const uint32_t num_threads) {
	omp_set_num_threads(num_threads);

	#pragma omp parallel shared(samples, clusters, new)
	{
		uint32_t thread_id = omp_get_thread_num();
		#pragma omp for schedule(static)
		for (uint32_t i = 0; i < sample_count; i++) {
			float min_distance = euclidean_distance_squared(&samples[i], &clusters[0]);
			uint32_t cluster_id = 0;

			for (uint32_t j = 1; j < cluster_count; j++) {
				float distance = euclidean_distance_squared(&samples[i], &clusters[j]);
				if (distance < min_distance) {
					min_distance = distance;
					cluster_id = j;
				}
			}

			// Instead of [cluster_count] we use [num_threads][cluster_count]
			// This way we can iterate over num_threads samples at a time and not be worried about data races.
			new[thread_id][cluster_id].x_sum += samples[i].x;
			new[thread_id][cluster_id].y_sum += samples[i].y;
			new[thread_id][cluster_id].total++;
		}
	}
}

/**
 * @brief The parallel k-means algorithm.
 *        Uses openmp to parallelize the calculation.
 *
 * @param points The points.
 * @param clusters The clusters.
 * @param cluster_count The number of clusters.
 * @param sample_count The number of points.
 * @return k_means_out
 */
k_means_out k_means_par(const point* samples, point* clusters, const uint32_t sample_count, const uint32_t cluster_count, const uint32_t num_threads) {
	uint32_t iter = 0;

	k_means_out out = k_means_out_init(cluster_count);
	k_means_aux** old = k_means_aux_init_2d(cluster_count, num_threads); // [num_threads][cluster_count]
	k_means_aux** new = k_means_aux_init_2d(cluster_count, num_threads); // [num_threads][cluster_count]

	// Step 1c - Assign each sample to the nearest cluster using the euclidean distance.
	k_means_par_cluster_points(samples, clusters, new, sample_count, cluster_count, num_threads);

	do {
		// Step 2 - Calculate the centroid of each cluster.
		k_means_par_recalc_clusters(clusters, cluster_count, &new[0], num_threads);

		// Delete previous iter's metrics: set "new" to "old" and "new" to 0
		memcpy(old, new, sizeof(k_means_aux*) * num_threads);
		for (uint32_t i = 0; i < num_threads; i++)
			memset(new[i], 0, sizeof(k_means_aux) * cluster_count);

		// Step 3 - Assign each sample to the nearest cluster using the euclidean distance
		k_means_par_cluster_points(samples, clusters, new, sample_count, cluster_count, num_threads);

		iter++;
	} while (k_means_par_has_converged(iter));

	// fill the output struct
	for (uint32_t i = 0; i < cluster_count; i++) {
		for (uint32_t j = 0; j < num_threads; j++) {
			out.cluster_size[i] += new[j][i].total;
		}
	}

	out.iterations = iter;

	// Free the allocated memory
	free(old);
	free(new);

	return out;
}
