#!/bin/bash
#SBATCH --job-name=k_means_par
#SBATCH --cpus-per-task=4
#SBATCH --output=k_means_16_4.out
date

echo "Running K-Means with 10000000 samples 16 clusters 4 threads"

# Run the program
./bin/k_means 10000000 16 4
