#!/bin/bash

find $1 -name "*.log" | while read name; 
do 
	cat $name | sort > $name-backup
	mv $name-backup $name
done
