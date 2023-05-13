#!/bin/bash
tmpfile=$(mktemp)
if [ ! -f "results_$1.txt" ]; then
    echo "algo;size;cost;expn;time(s)" > results_$1.txt
fi

while read cmd;
do
    $cmd >> results_$1.txt & 
done < sequences.txt