#!/bin/bash

touch benchmark.csv

num_for_repeat=5

echo "Threads,Dimension,MultTime,RunTime" > benchmark.csv

for omp_threads in 1 2 3 4 
do
	export OMP_NUM_THREADS=$omp_threads
	for dim in 900 1100 1300 1500
	do
		for ((i=0; i < $num_for_repeat; i++))
		do
		./mainCpp/main $dim >> benchmark.csv
		done
	done
done