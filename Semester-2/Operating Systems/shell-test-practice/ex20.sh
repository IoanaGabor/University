#!/bin/bash

while true;
do
	users=$@
	if [ "$users" = "" ]; then
	 	users=`cut -d: -f1 /etc/passwd`
	fi
	for user in $users;
	do
		pc=`ps -ef | cut -d " " -f1 | grep "$user" | wc -l`
		echo $pc $user
	done | sort -n -r
	sleep 1
done




