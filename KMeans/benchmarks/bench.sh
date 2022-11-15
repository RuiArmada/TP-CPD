#!/bin/bash

# Runs all the benchmarks in order
sbatch --partition=cpar benchmarks/4/4.sh
sbatch --partition=cpar benchmarks/4/4_2.sh
sbatch --partition=cpar benchmarks/4/4_4.sh
sbatch --partition=cpar benchmarks/4/4_8.sh
sbatch --partition=cpar benchmarks/4/4_16.sh
sbatch --partition=cpar benchmarks/4/4_32.sh

sbatch --partition=cpar benchmarks/8/8.sh
sbatch --partition=cpar benchmarks/8/8_2.sh
sbatch --partition=cpar benchmarks/8/8_4.sh
sbatch --partition=cpar benchmarks/8/8_8.sh
sbatch --partition=cpar benchmarks/8/8_16.sh
sbatch --partition=cpar benchmarks/8/8_32.sh

sbatch --partition=cpar benchmarks/16/16.sh
sbatch --partition=cpar benchmarks/16/16_2.sh
sbatch --partition=cpar benchmarks/16/16_4.sh
sbatch --partition=cpar benchmarks/16/16_8.sh
sbatch --partition=cpar benchmarks/16/16_16.sh
sbatch --partition=cpar benchmarks/16/16_32.sh

sbatch --partition=cpar benchmarks/32/32.sh
sbatch --partition=cpar benchmarks/32/32_2.sh
sbatch --partition=cpar benchmarks/32/32_4.sh
sbatch --partition=cpar benchmarks/32/32_8.sh
sbatch --partition=cpar benchmarks/32/32_16.sh
sbatch --partition=cpar benchmarks/32/32_32.sh

echo "All benchmarks submitted"
