#!/bin/bash


declare -i time_start
declare -i time_diff
declare -i get_timestamp_return_value

MAXTIME=10
NUMTRI=5
STARTSIZE=1000

function get_timestamp {
        declare -i time_curr=`date +%s`
        get_timestamp_return_value=$time_curr
}

function timer_start {
		get_timestamp
        time_start=get_timestamp_return_value
}

function timer_stop {
	get_timestamp
    declare -i time_curr=get_timestamp_return_value
    time_diff=$time_curr-$time_start
}

INFO=$(grep 'model name' /proc/cpuinfo | head -1 2>&1)
echo Starting tests....
echo "" >> $1
echo $INFO >> $1
echo "user, host, threads, particles, grainsize, seconds" >> $1

STARTGRAIN=$(echo $STARTSIZE | bc)
START=$(printf "%.0f" $STARTGRAIN)
PERGRAIN=$(echo  $START*0.10 | bc)
PER=$(printf "%.0f" $PERGRAIN)
echo "start: $START end: 1, per: $PER"

for ((i=$START; i > 0; i= i-$PER))
do 
	timer_start
    ./driver-reduce --particles $2 --trials $NUMTRI --grainsize $i --threads $3 >> $1
    echo "Completed grainsize $i ..."
    timer_stop
    DIFF=$(echo "$time_diff/$NUMTRI" | bc)	
	if [ $DIFF -ge $MAXTIME ]; then
		echo "Exiting. Hit Timeout..."
		break;
	fi

	if [ $PER -eq $i ]; then
		PERGRAIN=$(echo  $PER*0.10 | bc)
		PER=$(printf "%.0f" $PERGRAIN)
		if [ $PER -eq 0 ]; then
			break;
		fi
	fi
done
echo "Done sort test"
