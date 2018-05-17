#!/bin/bash

touch surface.csv
touch surface2.csv
touch surface4.csv


num_for_repeat=1


for omp_threads in 1 
do
	export OMP_NUM_THREADS=$omp_threads
	for iters in 999
	do
		for ((i=0; i < $num_for_repeat; i++))
		do
		./main/main $iters > surface.csv
		done
	done
done


for omp_threads in 2
do
	export OMP_NUM_THREADS=$omp_threads
	for iters in 999
	do
		for ((i=0; i < $num_for_repeat; i++))
		do
		./main/main $iters > surface2.csv
		done
	done
done


for omp_threads in 4
do
	export OMP_NUM_THREADS=$omp_threads
	for iters in 999
	do
		for ((i=0; i < $num_for_repeat; i++))
		do
		./main/main $iters > surface4.csv
		done
	done
done