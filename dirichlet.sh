#!/bin/bash

touch surface.csv

num_for_repeat=1


for omp_threads in 1
do
	export OMP_NUM_THREADS=$omp_threads
	for dim in 99
	do
		for ((i=0; i < $num_for_repeat; i++))
		do
		./main/main $iters >> surface.csv
		done
	done
done