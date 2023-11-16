#!/bin/bash

clear
rm ./output/extracted_values.log

for i in {1..16}; do
  # task=$((2**i))
  core=$i
  rm ./output/output-$core-core.txt
  
  sbatch --cpus-per-task=$core --job-name="ssc-$core-thread" --output=./output/output-$core-core.txt automated.sh
done