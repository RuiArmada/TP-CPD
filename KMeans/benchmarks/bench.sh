#!/bin/bash

PREFIX="perf stat -r 20 ./bin/k_means "

# wait function
wait_jobs(lc) {
    while [ $(squeue -u $USER | wc -l) -gt $lc ]; do sleep 2; done
}

for i in 4 8 16 32
do
    for j in 2 4 8 16
    do
        # SeARCH limits the number of parallel jobs to 2
        wait_jobs(2)
        $PREFIX 10000000 $i $j
    done
done

# run the rest of the benchmarks
wait_jobs(2)
$PREFIX 10000000 4
wait_jobs(2)
$PREFIX 10000000 8
wait_jobs(2)
$PREFIX 10000000 16
wait_jobs(2)
$PREFIX 10000000 32

# wait for all jobs to finish
wait_jobs(1)

# prepare the output folder
mkdir -p output
mv *.out output
tar -cf output.tar output
