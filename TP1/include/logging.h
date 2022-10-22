/**
 * @file logging.h
 * @brief Logging functions to be used by the application.
 * @version 0.1
 * @date 2022-10-21
 */

#ifndef LOGGING_H_
#define LOGGING_H_

#include <stdio.h>

#include "../include/utils.h"

/**
 * @brief Logs a message to the console.
 *
 * @param K Number of clusters
 * @param N Number of samples
 * @param iterations Number of iterations
 * @param clusters Array of clusters
 */
void log_message_to_console(int k, int n, int iterations, point* clusters);

/**
 * @brief Logs a message to a file.
 *
 * @param file File to write to
 * @param K Number of clusters
 * @param N Number of samples
 * @param iterations Number of iterations
 * @param clusters Array of clusters
 */
void log_message_to_file(FILE* file, int k, int n, int iterations, point* clusters);

/**
 * @brief Generates a filename for the log file.
 *
 * @param filename
 */
void generate_filename(char* filename);

/**
 * @brief Generates a file to log the message to.
 *
 * @param filename
 * @return FILE*
 */
FILE* generate_file(const char* filename);

#endif