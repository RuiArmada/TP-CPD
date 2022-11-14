#ifndef IMPL_EUCLIDEAN_DISTANCES_H
#define IMPL_EUCLIDEAN_DISTANCES_H

#include <inttypes.h>


typedef struct point point;

/**
 * @brief Returns the euclidean distance between two points.
 *        This function performs a single calculation.
 *        WARNING: This functions is for reference only.
 *                 It is not used in the final version.
 *
 * @param p1
 * @param p2
 * @return float
 */
float euclidean_distance_sqrt(const point* p1, const point* p2);

/**
 * @brief Returns the squared euclidean distance between two points.
 *        This function performs a single calculation.
 *
 * @param p1     The first point.
 * @param p2     The second point.
 * @return float The squared euclidean distance between the two points.
 */
float euclidean_distance_squared(const point* p1, const point* p2);

/**
 * @brief Returns the euclidean distance between two points.
 *        This function performs 4 calculations at a time.
 *        Takes 4 points from p1 and compares them to a single point p2.
 *        The results are stored in the output array.
 *
 * @param p1        The point array to calculate the distances from.
 * @param p2        The point to compare against.
 * @param uint32_t  The number of clusters.
 * @param output    The output array. Must be of size num_clusters.
 */
void euclidean_distance(const point* p1, const point* p2, uint32_t num_clusters, float* output);



#endif