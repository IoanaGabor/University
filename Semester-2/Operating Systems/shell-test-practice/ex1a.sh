#!/bin/bash -x

if [ $# -lt 1 ]; then
	echo "insufficient args"
	exit
fi	

if [ -d $1]; then
	echo "not a folder"
	exit
fi

counter=0
files=`find $1 -type f -name "*.c"` 
for fname in $files; do
	if [ -f "$1/$files"]; then
		let counter=$counter+`grep -E -c -v "^[ \t]*$" "$fname"`  #only one process here, better
	fi
done
echo $counter
