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

if (argc < 3) { // if invalid number of arguments provided

fprintf(stderr,"ping2: Exactly 2 or more arguments required, Usage: ./ping2 [IP version] [arguments for ping or ping6]\n");
return -1;

}

char version[2]; // version number
char* args = malloc(80000);
char* full_command = malloc(80000); // allocate memory for full command

if (full_command == NULL || args == NULL) {

perror("");
if (full_command != NULL) free(full_command);
else free(args);
return -1;

}

/* Copy arguments */

strncpy(version,argv[1],2); 
strncpy(args,argv[2],80000);

for (unsigned int i = 3; i < argc; i++) {

strncat(args," ",1);
strncat(args,argv[i],80000);

}


/* Check version number */

if (!strcmp(version,"4")) { // IPv4

strncpy(full_command,"ping ",5);
strncat(full_command,args,80000);

}
else if (!strcmp(version,"6")) { // IPv6

strncpy(full_command,"ping6 ",6);
strncat(full_command,args,80000);

}
else { // invalid version

fprintf(stderr,"ping2: invalid IP version provided\n");
free(full_command); // free memory
free(args);
return -1;

}

system(full_command); // execute on system

free(full_command); // free memory
free(args);

return 0;

}



