#!/bin/bash 

cat df.fake | tail -n +2 |  awk '{print $6 "#" $3 "#" $5}' | while read line;
do
	#echo $line
	filesys=`echo $line | cut -d# -f1`
	size=`echo $line | cut -d# -f2 | sed 's/M//'`
	percentage=`echo $line | cut -d# -f3 | sed 's/%//'`
	if [ $size -lt 1024 ] || [ $percentage -gt 80 ] ; then
		echo $filesys
	fi
done
