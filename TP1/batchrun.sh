#!/bin/bash

for i in {1..15}
do
   echo "Running batch number $i"
   echo
   make run
   echo
   echo
done
   echo "All batches have been compiled. Script has ended."