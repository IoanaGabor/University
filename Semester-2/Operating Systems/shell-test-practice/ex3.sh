#!/bin/bash

#while read string;
#do
#	if [ -r "$string" ]; then
#		echo "readable file"
#		break;
#	fi
#done

string=""
while [ ! -r "$string" ]; do
	read string
done
echo "readable file"
