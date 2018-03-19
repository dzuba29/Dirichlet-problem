#!/bin/bash
for var in 1 2 3 4
do 

export OMP_NUM_THREADS=$var

echo "threads:" $var
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