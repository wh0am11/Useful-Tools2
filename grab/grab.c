#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


/*
##############
#
# Author: wh0am1 
# Description: Finds full, complete words in a file
# Date: 9-15-17
#
##############
*/

void error(const char* msg);
void analyze(char* buffer,char* word);
void analyze_line(char* line,int num,char* word);
int determine_size(FILE* fp);

int main(int argc,char* argv[]) {

	if (argc != 3) {

		error("Usage: grab [word] [filename]\n");
		return -1;

	}

	FILE* fp = NULL;
	char* buffer = NULL;
	char word[100] = { 0 };
	int size = 0;

	strncpy(word,argv[1],100);
	
	fp = fopen(argv[2],"r");

	if (!fp) 
		error("");

	printf("* Opened file\n");
	
	size = determine_size(fp);
	buffer = malloc(size+1);

	if (!buffer) {

		if (fp) 
			fclose(fp);
		error("");
	}

	if (fread(buffer,1,size,fp) == -1) {

		if (fp) 
			fclose(fp);
		error("");
	}

	printf("* Read file\n");
	
	analyze(buffer,word);

	printf("* Closed file\n");

	fclose(fp);

	return 0;

}

int determine_size(FILE* fp) {

	/* Determine size of file */

	int size = 0;

	fseek(fp,0,SEEK_END);
	size = ftell(fp);
	rewind(fp);

	return size;
	

}

void analyze(char* buffer,char* word) {

	/* Analyze buffer with word */

	char* line = NULL;
	int line_num = 1;

	line = strtok(buffer,"\n");

	if (line) 
		analyze_line(line,line_num,word);

	while (line) {

		line = strtok(NULL,"\n");

		if (line) {

			++line_num;
			analyze_line(line,line_num,word);

		}
		else {
			
			break;
		}

	}
	

}

void analyze_line(char* line,int num,char* word) {

	/* Analyze line with word */

	char* w = NULL;
	char* s = NULL;
	char* full_copy = NULL;
	char** sptr = &s;
	int wnum = 1;

	full_copy = malloc(strlen(line)+1);

	if (!full_copy) {

		error("");
		exit(1);

	}

	strncpy(full_copy,line,strlen(line));

	w = strtok_r(line," ",sptr);

	if (w) {

		if (!strcmp(w,word)) 
			printf("* line %d word %d: %s\n",num,wnum,full_copy);
	}

	while (w) {

		w = strtok_r(NULL," ",sptr);

		++wnum;

		if (w) {
			
			if (!strcmp(w,word))
				printf("* line %d word %d: %s\n",num,wnum,full_copy);

		}
		else {
			break;

		}

	}


}

void error(const char* msg) {

	/* Report an error */

	if (errno)
		perror(msg);
	else 
		fprintf(stderr,"grab: %s\n",msg);

	exit(1);

}
