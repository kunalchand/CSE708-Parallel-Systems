#!/bin/bash

#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=4

#SBATCH --constraint=IB|OPA
#SBATCH --time=00:10:00

#SBATCH --partition=general-compute
#SBATCH --qos=general-compute

#SBATCH --cluster=ub-hpc
#SBATCH --reservation=ubhpc-future

#SBATCH --job-name="ssc_4_threads"
#SBATCH --output=output_openmp.txt

#SBATCH --exclusive

module load intel

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

gcc -fopenmp -o compiled_file ssc_openmp.c
./compiled_file
