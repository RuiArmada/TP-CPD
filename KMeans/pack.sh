#!/bin/bash

# Packs all the .out files into a single .tar.gz file.

mkdir -p output

mv *.out output

tar -czf output$(date +%Y_%m_%d_%H_%M_%S).tar.gz output

rm -rf output
