#!/bin/bash
for var in 1 2 3 4
do 

export OMP_NUM_THREADS=$var

echo "threads:" $var
echo "╔═══════════════════════════════════╗"
echo "║   dim    ║      mul    ║  runtime ║"
echo "╟───────────────────────────────────╢"
./mainCpp/main 500
./mainCpp/main 1000
./mainCpp/main 1500
./mainCpp/main 2000
echo "╚═══════════════════════════════════╝"

done