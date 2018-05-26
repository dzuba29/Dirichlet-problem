#!/bin/bash
#SBATCH --job-name=multi_matrix_potashev
#SBATCH --output=benchmark_cluster.csv
#SBATCH --ntasks=1
#
#SBATCH --cpus-per-task=20
#
#SBATCH --time=55:00
#SBATCH --mem-per-cpu=100

num_for_repeat=5

echo "Threads,Dimension,MultTime,RunTime" 
for omp_threads in 1 2 4 6 8 10 12 13 14 15 16 17 18 19 20
do

export OMP_NUM_THREADS=$omp_threads

for dim in 500 1000 1500 2000
do
	for ((i=0; i < $num_for_repeat; i++))
	do
	./main/main $dim 
	done
done

done