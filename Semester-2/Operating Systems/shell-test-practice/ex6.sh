#!/bin/bash 

filename=""
while [ "$filename" != "stop" ]
do
	read filename
	if [ ! -f $filename ] ; then
		echo "not a filename"
	else
		ftype=`file -b "$filename"`
		if [ $fytpe="ASCII text" ]; then
			echo "text file"
			echo "number of words on the first line $((`head -n1 "$filename" | wc -w`))"
		fi
	fi

done
