#!/bin/bash



###################
#
# Author: wh0am1
# Description: Commits files in the current directory
# Date: 9-15-17
#
####################


if [[ "$1" == "" ]]
then

	echo "Error: Couldn't commit file" 2>&1

else

	directory=""

	if [[ "$2" != "" ]]
	then
		directory=$2
	else
		directory="."
	fi

	echo $directory

	cd $directory

	git add .
	git commit -m "$1"
	git push origin master

fi
