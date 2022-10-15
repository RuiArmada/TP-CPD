#ifndef UTILS_H_
#define UTILS_H_

// point struct
typedef struct {
    float x;
    float y;
} point;

void gen_samples(point* samples, point* clusters, int n_samples, int n_clusters);

#endif