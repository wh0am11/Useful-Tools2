#!/bin/bash



############################
#
# Author: wh0am1
# Description: Moves everything in the current directory into a directory of your choice
# Date: 9-16-17
#
############################



if [[ "$1" == "" ]]
then
	echo "Error argument must be provided"
	exit
fi

if [[ ! -d $1 ]]
then
	mkdir -p $1
fi

for i in $(ls)
do
	if [[ -f $i ]]
	then
		mv "$i" "$1"
	fi

done
