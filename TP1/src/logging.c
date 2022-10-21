#include "../include/logging.h"

#include <stdlib.h>
#include <time.h>

void log_message_to_console(const char* message) {
    printf("[INFO] %s\n", message);
}

void log_message_to_file(const char* message, FILE* file) {
    fprintf(file, "[INFO] %s\n", message);
}

inline void generate_filename(char* filename) {
    time_t t = time(NULL);
    struct tm info = *localtime(&t);
    strftime(filename, 64, "%d/%m/%y_%X.log", &info);
}

FILE* generate_file(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s. Exiting...", filename);
        exit(EXIT_FAILURE);
    }
    return file;
}

void generate_message(char* message, int K, int N, int iterations, cluster* clusters) {
    sprintf(message, "N = %d, K = %d", N, K);
    for (int i = 0; i < K; i++) {
        sprintf(message, "Center: (%f, %f) : Size: %d", clusters[i].center->x, clusters[i].center->y, clusters[i].total);
    }
    sprintf(message, "Iterations: %d", iterations);
}
