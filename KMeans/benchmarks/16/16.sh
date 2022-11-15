#!/bin/bash
#SBATCH --job-name=k_means_par
#SBATCH --cpus-per-task=1
#SBATCH --output=k_means_16_1.out
date

echo "Running K-Means with 10000000 samples 16 clusters, sequential"

# Run the program
./bin/k_means 10000000 16