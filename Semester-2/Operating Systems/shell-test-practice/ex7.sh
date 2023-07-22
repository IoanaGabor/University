#!/bin/bash

if [ $(("$#" % 2)) -eq 1 ]; then
	echo "odd number of args"
	exit
fi

while [ "$#" -gt 0 ];
do
	filename="$1"
	word="$2"

	if [ ! -f "$filename" ]; then
		echo "${filename} not a file"
	else
		occ=`grep -o -E "\<$word\>" "$filename" | wc -l`
		if [ "$occ" -gt 2 ]; then
			echo "appears at least 3 times"
		else
			echo "appears at most 2 times"
		fi
	fi

	shift 2
done
