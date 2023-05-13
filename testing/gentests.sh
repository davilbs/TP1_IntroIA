#!/bin/bash
rm sequences.txt
algos=$3

for i in $(seq 1 $1);
do
    seq=$(shuf -i1-$2)
    for a in $algos;
    do
        echo "./TP1 $a $2" $seq >> sequences.txt
    done
done

sort -u -o sequences.txt sequences.txt