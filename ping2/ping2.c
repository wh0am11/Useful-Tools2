/*
#################
#
# Author: wh0am1 
# Description: A hack that combines ping and ping6 for simple usage
# Date: 8-1-17
#
#################
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc,char* argv[]) {

if (argc != 3) { // if invalid number of arguments provided

fprintf(stderr,"ping2: Exactly 2 arguments required, Usage: ./ping2 [IP version] [arguments for ping or ping6]\n");
return -1;

}

char version[2]; // version number
char args[strlen(argv[2])+1]; // arguments 
char* full_command = malloc(strlen(argv[2])+7); // allocate memory for full command

if (full_command == NULL) {

perror("");
return -1;

}

/* Copy arguments */

strncpy(version,argv[1],2); 
strncpy(args,argv[2],strlen(argv[2]));

/* Check version number */

if (!strcmp(version,"4")) {

strncpy(full_command,"ping ",5);
strncat(full_command,args,strlen(argv[2]));

}
else if (!strcmp(version,"6")) {

strncpy(full_command,"ping6 ",6);
strncat(full_command,args,strlen(argv[2]));

}
else {

fprintf(stderr,"ping2: invalid IP version provided\n");
free(full_command); // free memory
return -1;

}

system(full_command); // execute on system

free(full_command); // free memory

return 0;

}



