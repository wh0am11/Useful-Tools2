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

		error("Invalid number of arguments");
		return -1;

	}

	FILE* fp = NULL;
	char* buffer = NULL;
	char word[100] = { 0 };
	int size = 0;

	strncpy(word,argv[2],100);
	
	fp = fopen(argv[1],"r");

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

		++line_num;

		line = strtok(NULL,"\n");

		if (line)
			analyze_line(line,line_num,word);
		else break;

	}
	

}

void analyze_line(char* line,int num,char* word) {

	/* Analyze line with word */

	char* w = NULL;
	char* s = NULL;
	char** sptr = &s;
	int wnum = 1;

	w = strtok_r(line," ",sptr);

	if (w) {

		if (!strcmp(w,word)) 
			printf("* line %d word %d\n",num,wnum);
	}

	while (w) {

		w = strtok_r(NULL," ",sptr);

		++wnum;

		if (w) {
			
			if (!strcmp(w,word))
				printf("* line %d word %d\n",num,wnum);

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
