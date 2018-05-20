#!/bin/bash

num_for_repeat=1

for omp_threads in 1 2 3 4
do
	export OMP_NUM_THREADS=$omp_threads
	for iters in 999
	do
		for ((i=0; i < $num_for_repeat; i++))
		do
		./main/main $iters > surface${omp_threads}.csv
		
		done
	done
done
