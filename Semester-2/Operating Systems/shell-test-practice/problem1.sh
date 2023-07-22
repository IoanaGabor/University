#!/bin/bash
cat who.fake | while read name; 
do
	name=`echo $name | cut -d " " -f 1`
	nb=`cat ps.fake | cut -d " " -f 1 | grep -c "$name"`
	echo $name $nb
done
