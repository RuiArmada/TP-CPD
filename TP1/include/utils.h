#ifndef UTILS_H_
#define UTILS_H_

/**
 * @brief Point structure
 *
 * int id - The id of the cluster this point belongs to
 * float x - The x coordinate of the point
 * float y - The y coordinate of the point
 * float d - The distance of the point to its cluster
 */
typedef struct {
    int id;   // cluster id, initialized to -1
    float x;  // x coordinate
    float y;  // y coordinate
    float d;  // current distance to the cluster
} point;

/**
 * @brief Generates a random number between 0 and 255 for each
 *        of the matrix's elements. Function as described in
 *        the assignment.
 *
 * @param samples The matrix to be filled with random values.
 * @param n_samples Size of the matrix (rows and columns).
 */
void gen_samples(point* samples, point* clusters, int n_samples, int n_clusters);

/**
 * @brief Returns the euclidean distance between two points.
 *
 * @param p1 First point
 * @param p2 Second point
 * @return float Euclidean distance between p1 and p2
 */
float euclidean_distance(point* p1, point* p2);

#endif