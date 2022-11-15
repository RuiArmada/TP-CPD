#!/bin/bash
#SBATCH --job-name=k_means_par
#SBATCH --cpus-per-task=32
#SBATCH --output=k_means_4_32.out
date

echo "Running K-Means with 10000000 samples 4 clusters 32 threads"

# Run the program
./bin/k_means 10000000 4 32