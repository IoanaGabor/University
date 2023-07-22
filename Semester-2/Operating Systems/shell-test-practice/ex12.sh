#!/bin/bash

find "$1" -type f | while read path; # you have to choose only the files, with type f
do
	name=`awk -F/ '{ print $NF }'`
	echo "$name"
done | sort | uniq -c | sort -n
