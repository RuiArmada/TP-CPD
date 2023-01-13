#include <cuda.h>
#include <cuda_profiler_api.h>

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "../include/kmeans.cuh"

/**
 * @brief Calculates the squared euclidean distance between two points
 *
 * @param x
 * @param y
 * @return __device__
 */
__device__ inline static
float euclidean_distance(const sample* x, const cluster* y) {
    return (x->x - y->x) * (x->x - y->x) + (x->y - y->y) * (x->y - y->y);
}

__global__
void cluster_points(
    sample* sx,
    cluster* cx,
    const uint32_t N,
    const uint32_t K
) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < N) {

        // set min_dist to the first cluster
        float min_dist = euclidean_distance(&sx[idx], &cx[0]);
        sx[idx].id = 0;

        for (uint32_t i = 1; i < K; i++) {
            float dist = euclidean_distance(&sx[idx], &cx[i]);
            if (dist < min_dist) {
                min_dist = dist;
                sx[idx].id = i;
            }
        }
    }
}

__global__
void recalc_clusters(cluster* cx, const uint32_t K) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < K) {
        cx[idx].x = cx[idx]._x / cx[idx]._c;
        cx[idx].y = cx[idx]._y / cx[idx]._c;
    }
}

__global__
void do_work(
    sample* sx,
    cluster* cx,
    const uint32_t K,
    const uint32_t N
) {
    int tdx = threadIdx.x;
    int idx = blockIdx.x * blockDim.x + tdx;
    // shared memory for the clusters
    extern __shared__ cluster s_cx[];

    // Clear the current clusters auxilary values.
    if (idx < K) {
        cx[idx]._x = 0.0;
        cx[idx]._y = 0.0;
        cx[idx]._c = 0;
    }

    // 
    if (tdx < K) {
        s_cx[tdx]._x = 0.0;
        s_cx[tdx]._y = 0.0;
        s_cx[tdx]._c = 0;
    }
    // synchronize threads before starting
    __syncthreads();

    // This part of the algorithm used to be in the cluster_points function
    // in the sequential/omp version. Due to changes in the algorithm, as well
    // as the fact that the structures were changed, this was moved here.
    if (idx < N) {
        int c_id = sx[idx].id;
        atomicAdd(&s_cx[c_id]._x, sx[idx].x);
        atomicAdd(&s_cx[c_id]._y, sx[idx].y);
        atomicAdd(&s_cx[c_id]._c, 1);
    }

    __syncthreads();

    if (tdx < K) {
        atomicAdd(&cx[tdx]._x, s_cx[tdx]._x);
        atomicAdd(&cx[tdx]._y, s_cx[tdx]._y);
        atomicAdd(&cx[tdx]._c, s_cx[tdx]._c);
    }
}


/**
 * @brief
 *
 * @param samples
 * @param clusters
 * @param K Cluster count
 * @param N Sample count
 */
uint32_t k_means_cuda(sample* sx, cluster* cx, uint32_t N, uint32_t K) {
    // Allocate device memory for clusters and samples.
    uint32_t iter = 0;
    sample* d_sx;
    cluster* d_cx;
    cudaMalloc((void**)&d_sx, N * sizeof(sample));
    cudaMalloc((void**)&d_cx, K * sizeof(cluster));

    // Copy samples and clusters to device memory.
    cudaMemcpy(d_sx, sx, N * sizeof(sample), cudaMemcpyHostToDevice);
    cudaMemcpy(d_cx, cx, K * sizeof(cluster), cudaMemcpyHostToDevice);

    // take the above for loop and convert it to a do-while loop
    do {
        // Step 1c - Assign each sample to the nearest cluster using the euclidean distance.
        cluster_points << < ceil(N / 256), 256 >> > (d_sx, d_cx, N, K);
        cudaDeviceSynchronize();

        // Step 2 - Calculate the centroid of each cluster. (also known as geometric center)
        do_work << < ceil(N + 255) / 256, 256, K * sizeof(cluster) >> > (d_sx, d_cx, K, N);
        cudaDeviceSynchronize();

        // Step 3 - Assign each sample to the nearest cluster using the euclidean distance.
        recalc_clusters << <ceil(K / 10), 10 >> > (d_cx, K);
        cudaDeviceSynchronize();
        iter++;
    } while (iter < MAX_ITER);

    //// Copy the clusters back to the host.
    cudaMemcpy(cx, d_cx, K * sizeof(cluster), cudaMemcpyDeviceToHost);

    // Free the device memory.
    cudaFree(d_sx);
    cudaFree(d_cx);

    return iter;
}
