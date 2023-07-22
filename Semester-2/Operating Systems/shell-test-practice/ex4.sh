#!/bin/bash

#for arg in $*;
#do
#	if [ ! -f "$arg" ] || [ -d "$arg" ]; then
#		echo "$arg is not a regular file"
#		exit -1
#	fi
#done

#du -b $* | sort -n

for arg in $*;
do
	if test -f "$arg"; then
		du -b "$arg"
	fi
done | sort -n
