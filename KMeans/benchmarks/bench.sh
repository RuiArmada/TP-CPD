#!/bin/bash

module load gcc/7.2.0

# Runs all the benchmarks in order
sbatch benchmarks/4/4.sh
sbatch benchmarks/4/4_2.sh
sbatch benchmarks/4/4_4.sh
sbatch benchmarks/4/4_8.sh
sbatch benchmarks/4/4_16.sh
sbatch benchmarks/4/4_32.sh

sbatch benchmarks/8/8.sh
sbatch benchmarks/8/8_2.sh
sbatch benchmarks/8/8_4.sh
sbatch benchmarks/8/8_8.sh
sbatch benchmarks/8/8_16.sh
sbatch benchmarks/8/8_32.sh

sbatch benchmarks/16/16.sh
sbatch benchmarks/16/16_2.sh
sbatch benchmarks/16/16_4.sh
sbatch benchmarks/16/16_8.sh
sbatch benchmarks/16/16_16.sh
sbatch benchmarks/16/16_32.sh

sbatch benchmarks/32/32.sh
sbatch benchmarks/32/32_2.sh
sbatch benchmarks/32/32_4.sh
sbatch benchmarks/32/32_8.sh
sbatch benchmarks/32/32_16.sh
sbatch benchmarks/32/32_32.sh
