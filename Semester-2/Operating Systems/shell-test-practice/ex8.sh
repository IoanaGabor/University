#!/bin/bash


for arg in $@;
do
	if [ -f "$arg" ]; then
		echo `du -b "$arg"`
	fi
done | sort -r -n
