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

	elif [[ "$2" == "--move-dirs" && -d $i ]]
	then
		mv "$i"	"$1" 2>>/dev/null # A lazy but efficient way to get rid of the "cannot move subdirectory into itself" error
	fi

done
