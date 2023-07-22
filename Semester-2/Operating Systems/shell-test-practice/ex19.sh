#!/bin/bash

users=`cat /etc/passwd | awk -F: '{print $1}'`
for user in $users;
do
	ipaddr=`last -i| awk '{print $1" "$3}' | grep "$user" | cut -d " " -f2`
	if [ "$ipaddr" != "" ]; then
		echo "$ipaddr" > "${user}_ips.txt"
	fi
done
