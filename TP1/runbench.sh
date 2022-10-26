#!/bin/bash

DATE=`date +%d_%m_%y_%H:%M:%S`

echo "Starting benchmarks starting on $DATE"

srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_sqr > benchmarks/results/kmeans_$DATE.log

srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic_ffm_lto_omp > benchmarks/results/kmeans_o3_tlic_ffm_lto_omp_$DATE.log

# All other benchmarks use Euclidean distance using sum of squares
srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans > benchmarks/results/kmeans_$DATE.log
srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_u2 > benchmarks/results/kmeans_u2_$DATE.log
srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_u4 > benchmarks/results/kmeans_u4_$DATE.log
srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_u8 > benchmarks/results/kmeans_u8_$DATE.log
srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_b > benchmarks/results/kmeans_b_$DATE.log
srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_bu2 > benchmarks/results/kmeans_b_u2_$DATE.log
srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_bu4 > benchmarks/results/kmeans_b_u4_$DATE.log
srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_bu8 > benchmarks/results/kmeans_b_u8_$DATE.log

srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3 > benchmarks/results/kmeans_o3_$DATE.log
srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_u2 > benchmarks/results/kmeans_o3_u2_$DATE.log
srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_u4 > benchmarks/results/kmeans_o3_u4_$DATE.log
srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_u8 > benchmarks/results/kmeans_o3_u8_$DATE.log
srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_b > benchmarks/results/kmeans_o3_b_$DATE.log
srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_bu2 > benchmarks/results/kmeans_o3_bu2_$DATE.log
srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_bu4 > benchmarks/results/kmeans_o3_bu4_$DATE.log
srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_bu8 > benchmarks/results/kmeans_o3_bu8_$DATE.log

srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic > benchmarks/results/kmeans_o3_tlic_$DATE.log
srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic_u2 > benchmarks/results/kmeans_o3_tlic_u2_$DATE.log
srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic_u4 > benchmarks/results/kmeans_o3_tlic_u4_$DATE.log
srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic_u8 > benchmarks/results/kmeans_o3_tlic_u8_$DATE.log

srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic_ffm > benchmarks/results/kmeans_o3_tlic_ffm_$DATE.log
srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic_ffm_u2 > benchmarks/results/kmeans_o3_tlic_ffm_u2_$DATE.log
srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic_ffm_u4 > benchmarks/results/kmeans_o3_tlic_ffm_u4_$DATE.log
srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic_ffm_u8 > benchmarks/results/kmeans_o3_tlic_ffm_u8_$DATE.log

srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic_ffm_lto > benchmarks/results/kmeans_o3_tlic_ffm_lto_$DATE.log
srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic_ffm_lto_u2 > benchmarks/results/kmeans_o3_tlic_ffm_lto_u2_$DATE.log
srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic_ffm_lto_u4 > benchmarks/results/kmeans_o3_tlic_ffm_lto_u4_$DATE.log
srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic_ffm_lto_u8 > benchmarks/results/kmeans_o3_tlic_ffm_lto_u8_$DATE.log

echo "Done"
