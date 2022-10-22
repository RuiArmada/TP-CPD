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
 * @param message The message to be logged.
 */
void log_message_to_console(const char* message);

/**
 * @brief Logs a message to a file.
 *
 * @param message The message to be logged.
 * @param file The file to log the message to.
 */
void log_message_to_file(const char* message, FILE* file);

/**
 * @brief Generates a filename for the log file.
 *
 * @param filename
 */
void generate_filename(char* filename);

/**
 * @brief Generates a message to be logged from args.
 *
 * @param message pointer to the message where the generated message will be stored.
 * @param k number of clusters.
 * @param n number of samples.
 * @param iterations number of iterations it took to converge.
 * @param clusters array of clusters.
 */
void generate_message(char* message, int k, int n, int iterations, point* clusters);

#endif