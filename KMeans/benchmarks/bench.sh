#!/bin/bash

for i in 4 8 16 32
do
    for j in 2 4 8 16
    do
        while [ $(squeue -u $USER | wc -l) -gt 2 ]; do sleep 2; done
        perf stat -r 20 ./bin/k_means $i $j
    done
done

# run the rest of the benchmarks
while [ $(squeue -u $USER | wc -l) -gt 2 ]; do sleep 2; done
perf stat -r 20 ./bin/k_means 10000000 4
while [ $(squeue -u $USER | wc -l) -gt 2 ]; do sleep 2; done
perf stat -r 20 ./bin/k_means 10000000 8
while [ $(squeue -u $USER | wc -l) -gt 2 ]; do sleep 2; done
perf stat -r 20 ./bin/k_means 10000000 16
while [ $(squeue -u $USER | wc -l) -gt 2 ]; do sleep 2; done
perf stat -r 20 ./bin/k_means 10000000 32

# wait for all jobs to finish
while [ $(squeue -u $USER | wc -l) -gt 2 ]; do sleep 2; done

# prepare the output folder
mkdir -p output
mv *.out output
tar -cf output.tar output
