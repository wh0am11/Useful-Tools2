#!/bin/bash



if [[ "$1" == "" || $2 == "" ]]
then

	echo "Error: Not able to add alias" 2>&1
else

	echo "alias $1=\"$2\"" >> ~/.bash_aliases

fi
