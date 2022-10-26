#ifndef KMEANS_H_
#define KMEANS_H_

#include "../include/bconsts.h"
#include "../include/utils.h"

typedef struct {
    int sizes[K];
    int iterations;
} k_means_out;

k_means_out k_means(point* samples, point* clusters);

#endif