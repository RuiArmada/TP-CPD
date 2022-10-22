#include "../include/logging.h"

#include <stdlib.h>
#include <time.h>

void log_message_to_console(int k, int n, int iterations, point* clusters) {
    printf("N = %d, K = %d\n", n, k);
    for (int i = 0; i < k; i++) {
        printf("Center: (%f, %f) : Size: %d\n", clusters[i].x, clusters[i].y, clusters[i].id);
    }
    printf("Iterations: %d\n", iterations);
}

void log_message_to_file(FILE* file, int k, int n, int iterations, point* clusters) {
    fprintf(file, "N = %d, K = %d\n", n, k);
    for (int i = 0; i < k; i++) {
        fprintf(file, "Center: (%f, %f) : Size: %d\n", clusters[i].x, clusters[i].y, clusters[i].id);
    }
    fprintf(file, "Iterations: %d\n", iterations);
}

inline void generate_filename(char* filename) {
    time_t t = time(NULL);
    struct tm info = *localtime(&t);
    strftime(filename, 30, "%d\\%m\\%y_%X.log", &info);
}

FILE* generate_file(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s. Exiting...", filename);
        exit(EXIT_FAILURE);
    }
    return file;
}
