#!/bin/bash

allids=`ps -ef| tail -n +2 | awk '{print $1" "$2}'`
users=`echo "$allids" | cut -d " " -f1 | sort | uniq`
while true; do
	echo "running"
done

for user in $users;
do
	ids=`echo "$allids" | grep "$user" | awk '{print $2}'`
	sum=0
	count=0
	for id in $ids;
	do
		sum=$(($sum + $id))
		count=$(($count + 1))
	done
	echo "average for user $user is $(($sum/$count))"	
done
#sum=0
#count=0
#for id in $ids;
#do
#	sum=$(($sum + $id))
#	count=$(($count + 1))
#done

#echo $(($sum / $count))
