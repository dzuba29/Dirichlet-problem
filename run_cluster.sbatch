#!/bin/bash
#SBATCH --job-name=Potashev_matrix
#SBATCH --output=output_%j.txt
#SBATCH --ntasks=1
#
#SBATCH --cpus-per-task=20
#
#SBATCH --time=10:00
#SBATCH --mem-per-cpu=100

for var in 20
do 

omp_threads=$var
export OMP_NUM_THREADS=$omp_threads

echo "threads:" $omp_threads
echo "╔═══════════════════════════════════╗"
echo "║   dim    ║      mul    ║  runtime ║"
echo "╟───────────────────────────────────╢"
./mainCpp/main 500
./mainCpp/main 700
./mainCpp/main 900
./mainCpp/main 1100
./mainCpp/main 1300
./mainCpp/main 1500
echo "╚═══════════════════════════════════╝"

done