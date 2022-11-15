
#include <immintrin.h>
#include <inttypes.h>
#include <math.h>
#include <omp.h>

#include "../include/common/point.h"
#include "../include/euclidean_distance.h"
#include "../include/common/builtins.h"


/**
 * @brief Returns the euclidean distance between two points.
 *
 * WARNING: This is here for reference only. It is not used in the program.
 *
 * @param p1
 * @param p2
 * @return float
 */
float euclidean_distance_sqrt(const point* p1, const point* p2) {
    return sqrtf(powf(p1->x - p2->x, 2) + powf(p1->y - p2->y, 2));
}

/**
 * @brief Returns the squared euclidean distance between two points.
 *
 * @param p1
 * @param p2
 * @return float
 */
inline float euclidean_distance_squared(const point* p1, const point* p2) {
    return powf(p1->x - p2->x, 2) + powf(p1->y - p2->y, 2);
}

/**
 * @brief Calculates the euclidean distance between a set of points and a point.
 *
 * @param p1     The point array to calculate the distances from.
 * @param p2     Point to compare against
 * @param output The output array. Must be of size num_clusters.
 */
inline void euclidean_distance_4pts(const point* p1, const point* p2, float* output) {
    output[0] = euclidean_distance_squared(&p1[0], p2);
    output[1] = euclidean_distance_squared(&p1[1], p2);
    output[2] = euclidean_distance_squared(&p1[2], p2);
    output[3] = euclidean_distance_squared(&p1[3], p2);
}

/**
 * @brief Returns the euclidean distance between sets of points.
 *        Uses SSE intrinsics to speed up the calculations of up to 4 points at a time.
 *
 * @param p1 Pointer to an array of points.
 * @param p2 Pointer to a single point.
 * @param output 4 float array to store the results.
 */
inline void euclidean_distance_squared_sse(const point* p1, const point* p2, float* output) {
    // Perhaps take this into account: https://stackoverflow.com/questions/49265634/what-is-the-difference-between-loadu-ps-and-set-ps-when-using-unformatted-data
    // Changing the way the data is stored in memory might improve locality and allow _mm_loadu_ps to be used instead of _mm_set_ps.
    // This would require changing the way the data is stored, from an array of structs [Point { .x: f32, .y: f32}] to two arrays of floats [Vec<f32>, Vec<f32>].
    __m128 p1x_packed = _mm_set_ps(p1[3].x, p1[2].x, p1[1].x, p1[0].x);
    __m128 p1y_packed = _mm_set_ps(p1[3].y, p1[2].y, p1[1].y, p1[0].y);
    __m128 p2x_packed = _mm_set_ps1(p2->x);
    __m128 p2y_packed = _mm_set_ps1(p2->y);

    // Calculate the differences between the x and y coordinates.
    // Latency: 4 cycles Throughput(CPI): 0.5
    __m128 x_diffs = _mm_sub_ps(p1x_packed, p2x_packed);
    // Latency: 4 cycles Throughput(CPI): 0.5
    __m128 y_diffs = _mm_sub_ps(p1y_packed, p2y_packed);

    // Square the differences.
    // Latency: 4 cycles Throughput(CPI): 0.5
    x_diffs = _mm_mul_ps(x_diffs, x_diffs);
    // Latency: 4 cycles Throughput(CPI): 0.5
    y_diffs = _mm_mul_ps(y_diffs, y_diffs);

    // Sum the squared differences.
    // Latency: 4 cycles Throughput(CPI): 0.5
    // Store the results.
    // Latency: 5 cycle Throughput(CPI): 1
    _mm_storeu_ps(output, _mm_add_ps(x_diffs, y_diffs));
}

/**
 * @brief Returns the euclidean distance between a set of points and clusters.
 *
 *
 * @param p1
 * @param p2
 * @param num_clusters
 * @param output
 */
inline void euclidean_distance(const point* p1, const point* p2, unused uint32_t num_clusters, float* output) {
    void (*dst_fn)(const point*, const point*, float*) = euclidean_distance_4pts;
    #ifdef USE_SSE // -DUSE_SSE=1 (defaults to 0)
    dst_fn = euclidean_distance_squared_sse;
    #endif
    dst_fn(&p1[0], p2, &output[0]);
}


