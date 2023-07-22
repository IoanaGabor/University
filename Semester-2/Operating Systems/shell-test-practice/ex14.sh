#!/bin/bash -x

while true;
do
	for prog in $*;
	do
		if ps -ef | awk '{print $8}'|grep -q -E "\<$prog"; then
			pid=`ps -ef | awk '{print $8" "$2}'|grep -E "\<$prog" | sed -E 's/[ \t]+/ /g' | cut -d " " -f2 | head -n1`
			kill -9 "$pid"
			echo "process $prog with pid $pid was killed"
	
			#for p in $pid:
			#do
			#	kill -9 "$p"
			#	echo "process $prog with pid $p was killed"
			#done

		fi
	done
	sleep 1
done
