#!/bin/bash
#SBATCH --job-name=multi_matrix
#SBATCH --output=benchmark_cluster.csv
#SBATCH --ntasks=1
#
#SBATCH --cpus-per-task=20
#
#SBATCH --time=10:00
#SBATCH --mem-per-cpu=100

num_for_repeat=5

echo "Threads,Dimension,MultTime,RunTime" 
for omp_threads in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
do

export OMP_NUM_THREADS=$omp_threads

for dim in 900 1100 1300 1500
do
	for ((i=0; i < $num_for_repeat; i++))
	do
	./mainCpp/main $dim 
	done
done

done