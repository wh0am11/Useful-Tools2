#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pwd.h>


/*
#########################
#
# Author: wh0am1
# Description: Prints a random ASCII picture on the start screen
# Date: 9-17-17
#
##########################
*/

void display_file(const char* display,const char* color);

int main(int argc,char* argv[]) {

	char* file_array[4] = { 
		"/home/wh0am1/code/Useful-Tools2/startscreen/l33t", "/home/wh0am1/code/Useful-Tools2/startscreen/hack",
		"/home/wh0am1/code/Useful-Tools2/startscreen/os", "/home/wh0am1/code/Useful-Tools2/startscreen/universe"
	};
	char* color[12] = { /* why the hell is light gray even a color code? It's the same as white? And who wants black? */

		"0;34", "0;32", "0;36", "0;31", "0;35", "0;33", 
		"1;34", "1;32", "1;36", "1;31", "1;35", "1;33"	
	
	}; 
	int index = 0;
	int color_index = 0;
	struct passwd* p;
	
	srand((unsigned int)time(NULL));

	index = rand() % 4;

	color_index = rand() % 13;

	display_file(file_array[index],color[color_index]);

	p = getpwuid(getuid());

	color_index = rand() % 13;

	printf("Welcome, \033[%sm%s\n\033[0;0m",color[color_index],p->pw_name);

	return 0;

}


void display_file(const char* display,const char* color) {

	/* Display a file's contents */

	FILE* fp = NULL;
	int size = 0;
	
	fp = fopen(display,"r");

	fseek(fp,0,SEEK_END);
	size = ftell(fp);
	rewind(fp);

	char buffer[size];

	fread(buffer,1,size,fp);

	fclose(fp);

	printf("\033[%sm\n%s\n\033[0;0m",color,buffer);


}

