#!/bin/bash

main_function() {

    DATE=`date +%d_%m_%y_%H:%M:%S`

    echo "Starting benchmarks starting on $DATE"

   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_sqrt ; } 2> benchmarks/results/kmeans.log

   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic_ffm_lto_omp ; } 2> benchmarks/results/kmeans_o3_tlic_ffm_lto_omp.log

    # All other benchmarks use Euclidean distance using sum of squares
   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans ; } 2> benchmarks/results/kmeans.log
   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_u2 ; } 2> benchmarks/results/kmeans_u2.log
   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_u4 ; } 2> benchmarks/results/kmeans_u4.log
   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_u8 ; } 2> benchmarks/results/kmeans_u8.log
   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_b ; } 2> benchmarks/results/kmeans_b.log
   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_bu2 ; } 2> benchmarks/results/kmeans_b_u2.log
   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_bu4 ; } 2> benchmarks/results/kmeans_b_u4.log
   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_bu8 ; } 2> benchmarks/results/kmeans_b_u8.log

   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3 ; } 2> benchmarks/results/kmeans_o3.log
   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_u2 ; } 2> benchmarks/results/kmeans_o3_u2.log
   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_u4 ; } 2> benchmarks/results/kmeans_o3_u4.log
   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_u8 ; } 2> benchmarks/results/kmeans_o3_u8.log
   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_b ; } 2> benchmarks/results/kmeans_o3_b.log
   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_bu2 ; } 2> benchmarks/results/kmeans_o3_bu2.log
   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_bu4 ; } 2> benchmarks/results/kmeans_o3_bu4.log
   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_bu8 ; } 2> benchmarks/results/kmeans_o3_bu8.log

   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic ; } 2> benchmarks/results/kmeans_o3_tlic.log
   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic_u2 ; } 2> benchmarks/results/kmeans_o3_tlic_u2.log
   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic_u4 ; } 2> benchmarks/results/kmeans_o3_tlic_u4.log
   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic_u8 ; } 2> benchmarks/results/kmeans_o3_tlic_u8.log

   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic_ffm ; } 2> benchmarks/results/kmeans_o3_tlic_ffm.log
   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic_ffm_u2 ; } 2> benchmarks/results/kmeans_o3_tlic_ffm_u2.log
   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic_ffm_u4 ; } 2> benchmarks/results/kmeans_o3_tlic_ffm_u4.log
   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic_ffm_u8 ; } 2> benchmarks/results/kmeans_o3_tlic_ffm_u8.log

   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic_ffm_lto ; } 2> benchmarks/results/kmeans_o3_tlic_ffm_lto.log
   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic_ffm_lto_u2 ; } 2> benchmarks/results/kmeans_o3_tlic_ffm_lto_u2.log
   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic_ffm_lto_u4 ; } 2> benchmarks/results/kmeans_o3_tlic_ffm_lto_u4.log
   { srun --partition=cpar perf stat -e cycles,instructions -r 20 ./benchmarks/bin/kmeans_o3_tlic_ffm_lto_u8 ; } 2> benchmarks/results/kmeans_o3_tlic_ffm_lto_u8.log

    echo "Done"
}

main_function 2>&1 | tee -a benchmarks/results/benchmarks.log