#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>

/*
######################
#
# Author: wh0am1
# Description: Creates C Files automatically without me having to write descriptions like this
# Date: 9-18-17
#
#####################
*/

int check_empty(char* str);
int write_data(char* name,char* author,char* desc,char* date);

int main(int argc,char* argv[]) {

	char name[1000] = "";
	char author[100] = "";
	char description[1000] = "";
	char date[100] = ""; 

	if (argc < 2) {

		fprintf(stderr,"Usage: gcreate [name] [author] [description] [date]\n");
		return -1;
	}
	else if (argc == 2) {

		strncpy(name,argv[1],1000);
	}
	else if (argc == 3) {
		
		strncpy(name,argv[1],1000);
		strncpy(author,argv[2],100);
	}
	else if (argc == 4)  {

		strncpy(name,argv[1],1000);
		strncpy(author,argv[2],100);
		strncpy(description,argv[3],1000);
	}
	else if (argc == 5) {

		strncpy(name,argv[1],1000);
                strncpy(author,argv[2],100);
                strncpy(description,argv[3],1000);
		strncpy(date,argv[4],100);

	}

	write_data(name,author,description,date);

	return 0;

}

int check_empty(char* str)  {

	/* Check if string is empty */

	if (!strcmp(str,"")) return 1;
	return 0;

}

int write_data(char* name,char* author,char* desc,char* date) {

	/* Write data into file */

	FILE* fp = NULL;
	char str[BUFSIZ];
	char nameext[BUFSIZ];
	
	strncpy(nameext,name,BUFSIZ);
	strncat(nameext,".c",2);

	fp = fopen(nameext,"w");

	if (!fp) return -1;
	
	strncpy(str,"#include <stdio.h>\n\n\n/*\n##############\n",BUFSIZ);

	if (check_empty(author) == 0) {
	
		strncat(str,"# Author: ",BUFSIZ);
		strncat(str,author,BUFSIZ);
		strncat(str,"\n",1);
	}
	else {

		struct passwd* p = getpwuid(getuid());

		strncat(str,"# Author: ",BUFSIZ);
		strncat(str,p->pw_name,BUFSIZ);
		strncat(str,"\n",1);

	}

	if (check_empty(desc) == 0) {

		strncat(str,"# Description: ",BUFSIZ);
		strncat(str,desc,BUFSIZ);
		strncat(str,"\n",1);

	}
	else {

		strncat(str,"# Description: A generic description\n",BUFSIZ);

	}

	if (check_empty(date) == 0) {

		strncat(str,"# Date: ",BUFSIZ);
		strncat(str,date,BUFSIZ);
		strncat(str,"\n",1);

	}
	else {
		
		time_t d = time(NULL);
		char* date = ctime(&d);

		strncat(str,"# Date: ",BUFSIZ);

		char* line = strtok(date," ");

		line = strtok(NULL," ");
		strncat(str,line,BUFSIZ);
		strncat(str," ",1);
		line = strtok(NULL," ");
		strncat(str,line,BUFSIZ);
		strncat(str," ",1);
		line = strtok(NULL," ");
		line = strtok(NULL," ");
		strncat(str,line,BUFSIZ);

	}
	strncat(str,"##############\n*/\n",BUFSIZ);
	strncat(str,"\n\nint main(int argc,char* argv[]) {\n\n\n\t/* Auto-generated C File */\n\n\treturn 0;\n\n\n}\n",BUFSIZ);

	fwrite(str,1,strlen(str),fp);

	fclose(fp);

	return 0;

}
