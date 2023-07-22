#!/bin/bash

for arg in $@;
do
	if [ -f "$arg" ] && `file -b "$arg" | grep -q "C source"`; then
		#echo "$arg is c source"
		lib=`grep -E -o "^#include ?<.*>$" "$arg"`
		echo "$lib"
	fi
done > ex9-libraries.txt
