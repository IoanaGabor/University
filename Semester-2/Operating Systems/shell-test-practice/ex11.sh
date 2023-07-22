#!/bin/bash

find "$1" | while read file;
do
	if [ -L "$file" ] ;then
		if [ ! -e "$file" ]; then
			echo "$file is a symlink that does not exist anymore"
		else
			echo "$file is a symlink that exists"
		fi
	fi
done
