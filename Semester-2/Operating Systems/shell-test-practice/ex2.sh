#!/bin/bash

count=$#
#while test $count -gt 0 ;
#while test ! $count -eq 0;
while [ ! $count -eq 0 ];
do
	if [ -d "$1" ]; then

		echo "directory"

	elif [ -f "$1" ]; then

		echo "file"

	elif echo "$1" | grep -q -E "\-?[1-9][0-9]*"; then

		echo "number"

	else
		echo "anything else"
	fi

	shift
	count=$(($count-1))
done
