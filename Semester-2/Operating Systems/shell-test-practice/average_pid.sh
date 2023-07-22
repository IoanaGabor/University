#!/bin/bash -x

ids=`ps -ef| tail -n +2 | awk '{print $2}'`

sum=0
count=0
for id in $ids;
do
	sum=$(($sum + $id))
	count=$(($count + 1))
done

echo $(($sum / $count))
