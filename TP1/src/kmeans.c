#include "../include/kmeans.h"

#include <math.h>

void k_means(point* samples, point* clusters);
void cluster_points();
void reevaluate_centers();
void has_converged();
void find_centers();

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
void cluster_points() {}

/*
def reevaluate_centers(mu, clusters):
    newmu = []
    keys = sorted(clusters.keys())
    for k in keys:
        newmu.append(np.mean(clusters[k], axis = 0))
    return newmu
*/
void reevaluate_centers() {}

/*
def has_converged(mu, oldmu):
    return (set([tuple(a) for a in mu]) == set([tuple(a) for a in oldmu])
*/
void has_converged() {}

/*
def find_centers(X, K):
    # Initialize to K random centers
    oldmu = random.sample(X, K)
    mu = random.sample(X, K)
    while not has_converged(mu, oldmu):
        oldmu = mu
        # Assign all points in X to clusters
        clusters = cluster_points(X, mu)
        # Reevaluate centers
        mu = reevaluate_centers(oldmu, clusters)
    return(mu, clusters)
*/
void find_centers() {}

void k_means(point* samples, point* clusters) {
    int step = 0;
    // Step 1b - Initialize the K clusters with the coordinates of the first K samples
    // Step 1c - Assign each sample to the nearest cluster using the euclidean distance

    do {
        // Step 2 - Calculate the centroid of each cluster (also known as geometric center)
        // Step 3 - Assign each sample to the nearest cluster using the euclidean distance
        step++;
    } while ((step < 100));  // Step 4 - Repeat steps 2 and 3 until there are no points that change clusters
}
