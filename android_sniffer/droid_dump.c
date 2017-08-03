/*
################
#
# Author: wh0am1
# Description: Sniff packets on Android without root permission 
# Date: 8-2-17
#
################
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "netinet/ip.h"

int main(int argc,char* argv[]) {


int s = socket(AF_INET,SOCK_RAW,0);

if (s == -1) {

perror("Error");
return -1;

}
else close(s);

return 0;

}
