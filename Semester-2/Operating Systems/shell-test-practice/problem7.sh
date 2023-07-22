#!/bin/bash

if [ -z "$1" ];then
	echo "expected 1 argument"
	exit
fi
usernames=""
names=`cat $1`
for name in $names; do
	usernames="${usernames} ${name}@scs.ubbcluj.ro,"
done
usernames=${usernames:1:-1}
echo $usernames
