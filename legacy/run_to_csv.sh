#!/bin/bash

touch benchmark_kji.csv

num_for_repeat=5

echo "Threads,Dimension,MultTime,RunTime" > benchmark_kji.csv

for omp_threads in 1 2 3 4 
do
	export OMP_NUM_THREADS=$omp_threads
	for dim in 500 1000 1500 2000
	do
		for ((i=0; i < $num_for_repeat; i++))
		do
		./main/main $dim >> benchmark_kji.csv
		done
	done
done