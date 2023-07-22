#!/bin/bash -x

if [ $# -lt 1 ]; then
	echo "insufficient args"
fi	

counter=0
files=`find $1 -type f -name "*.c"` 
for fname in $files; do
	
	#let counter=$counter+`cat $fname | sed 's/ //' | grep -E -c -v "^$"` 
	let counter=$counter+`grep -E -c -v "^[ \t]*$" "$fname"`  #only one process here, better
done
echo $counter
