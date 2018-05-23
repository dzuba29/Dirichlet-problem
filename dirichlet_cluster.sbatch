#!/bin/bash
#SBATCH --job-name=dirichlet
#SBATCH --output=result.csv
#SBATCH --ntasks=1
#
#SBATCH --cpus-per-task=20
#
#SBATCH --time=20:00
#SBATCH --mem-per-cpu=100

num_for_repeat=1

for omp_threads in 1 2 4 8 20
do
 export OMP_NUM_THREADS=$omp_threads
 for iters in 698
 do
  for ((i=0; i < $num_for_repeat; i++))
  do
  ./main/main $iters > surface${omp_threads}_${iters}.csv
  done
 done
done