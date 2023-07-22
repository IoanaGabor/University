#!/bin/bash

sum=0
for arg in $*;
do
	if [ -f "$arg" ] && [ ! -d "$arg" ]; then
		size=`du -b "$arg" | cut  -f 1`
		echo "$arg has size $size"
		sum=$(($sum+$size))
	fi
done
echo "total sum is $sum"
