#!/bin/bash
INFO=$(grep 'model name' /proc/cpuinfo | head -1 2>&1)
echo Starting tests....
echo "" >> $1
echo $INFO >> $1
echo "user, host, threads, particles, grainsize, seconds" >> $1
for ((i=$2; i > $2/25; i= i-$2/10))
do 
    ./driver-compute --particles $2 --trials 5 --grainsize $i --threads $3 >> $1
    echo "Completed grainsize $i ..."
done
echo "Done compute test"
