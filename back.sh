#!/bin/bash



######################
#
# Author: wh0am1
# Description: Goes back a directory (different from "cd -")
# Date: 9-11-17
#
######################



cwd=$(pwd)

new_cwd=${cwd%/*}

cd $new_cwd
