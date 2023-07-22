#!/bin/bash


if [ "$#" -gt 0 ] && [ ! -d "$1" ]; then
	echo "not a directory"
	exit
fi

if [ "$#" -eq 0 ]; then
	dir="."
else
	dir="$1"
fi

for file in $(ls "$dir" | grep -E ".*.sh$"); do
	size=`du -b "$dir/$file" | cut -f1`
	perm=`ls -l "$dir/$file" | cut -d " " -f1`
	ul=`sort $dir/$file | uniq | wc -l`
	echo "$dir/$file size $size permissions $perm unique lines $ul"

done

