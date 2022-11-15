#!/bin/bash

for i in 4 8 16 32
do
    for j in 2 4 8 16 32
    do
        while [ $(squeue -u $USER | wc -l) -gt 2 ]; do sleep 2; done
        sbatch --partition=cpar ./benchmarks/$i/$i\_$j.sh
    done
done

# run the rest of the benchmarks
while [ $(squeue -u $USER | wc -l) -gt 2 ]; do sleep 2; done
./benchmarks/4/4.sh
while [ $(squeue -u $USER | wc -l) -gt 2 ]; do sleep 2; done
./benchmarks/8/8.sh
while [ $(squeue -u $USER | wc -l) -gt 2 ]; do sleep 2; done
./benchmarks/16/16.sh
while [ $(squeue -u $USER | wc -l) -gt 2 ]; do sleep 2; done
./benchmarks/32/32.sh

# wait for all jobs to finish
while [ $(squeue -u $USER | wc -l) -gt 2 ]; do sleep 2; done

# prepare the output folder
mkdir -p output
mv *.out output
tar -cf output.tar output
