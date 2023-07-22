#!/bin/bash

count=0
find $1 -name "*.c" | while read file;
do
	lines=`wc -l "$file" | cut -d " " -f1`
	if [ $lines -gt 500 ]; then
		echo $file
		let count=count+1			
	fi
	if [ $count -eq 2 ]; then
		break;
	fi
done
