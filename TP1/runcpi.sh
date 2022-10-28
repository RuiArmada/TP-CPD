#!/bin/bash

# This script runs each of the programs with -M cpi


main_function() {

    DATE=`date +%d_%m_%y_%H:%M:%S`

    echo "Starting benchmarks starting on $DATE"

    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_sqrt > /dev/null

    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_u2 > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_u4 > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_u8 > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_b > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_bu2 > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_bu4 > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_bu8 > /dev/null

    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o2 > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o2_u2 > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o2_u4 > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o2_u8 > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o2_b > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o2_bu2 > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o2_bu4 > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o2_bu8 > /dev/null

    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o3 > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o3_u2 > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o3_u4 > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o3_u8 > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o3_b > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o3_bu2 > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o3_bu4 > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o3_bu8 > /dev/null

    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o2_tlic > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o2_tlic_u2 > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o2_tlic_u4 > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o2_tlic_u8 > /dev/null

    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o2_tlic_ffm > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o2_tlic_ffm_u2 > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o2_tlic_ffm_u4 > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o2_tlic_ffm_u8 > /dev/null

    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o2_tlic_ffm_lto > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o2_tlic_ffm_lto_u2 > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o2_tlic_ffm_lto_u4 > /dev/null
    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o2_tlic_ffm_lto_u8 > /dev/null

    srun --partition=cpar perf stat -e cycles,instructions -M cpi ./benchmarks/bin/kmeans_o2_tlic_ffm_lto_omp > /dev/null

    echo "Done"
}

main_function 2>&1 | tee -a benchmarks/results/cpi.log