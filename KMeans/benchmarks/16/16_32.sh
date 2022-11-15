#!/bin/bash
#SBATCH --job-name=k_means_par
#SBATCH --cpus-per-task=32
#SBATCH --output=k_means_16_32.out
date

echo "Running K-Means with 10000000 samples 16 clusters 32 threads"

# Run the program
perf stat ./bin/k_means 10000000 16 32
