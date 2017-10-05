#!/bin/bash



#################
#
# Author: wh0am1
# Description: Shows usage of directories returned from df
# Date: Oct 5 2017
#
##################



df -h | awk '{ print $5 "\t\t\t\t" $6 }'
