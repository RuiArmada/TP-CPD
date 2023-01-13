#ifndef KMEANS_H_
#define KMEANS_H_

#include <inttypes.h>

typedef struct {
    float x;
    float y;
    uint32_t id; // cluster_id
} sample;

typedef struct {
    float x;
    float y;
    float _x; // auxiliar x
    float _y; // auxiliar y
    uint32_t _c; // auxiliar point count
} cluster;

uint32_t k_means_cuda(sample* sx, cluster* cx, uint32_t K, uint32_t N);

// Edit this to change the number of iterations
#define MAX_ITER 20


#endif