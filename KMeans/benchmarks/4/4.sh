#!/bin/bash
#SBATCH --job-name=k_means_par
#SBATCH --cpus-per-task=1
#SBATCH --output=k_means_4_1.out
date

echo "Running K-Means with 10000000 samples 4 clusters, sequential"

# Run the program
perf stat ./bin/k_means 10000000 4
