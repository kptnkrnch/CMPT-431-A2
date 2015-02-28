#!/bin/bash
INFO=$(grep 'model name' /proc/cpuinfo | head -1 2>&1)
echo Starting tests....
echo '\n' >> $1
echo $INFO >> $1
for ((i=$2; i > $2/4; i= i-$2/10))
do 
    ./driver-sort --particles $2 --trials 5 --grainsize $i --threads $3 >> $1
    echo "Completed grainsize $i ..."
done
