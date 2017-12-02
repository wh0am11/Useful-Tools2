


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_DATA 5000

void write_file(FILE *fp, const char *data, const size_t data_len) {

	if (fwrite(data, data_len, 1, fp) < 0) {

		perror("gcreate");
		return;
	}

}

void write_h_file(FILE *fp) {

	const char *data = "#ifndef __something__\n#define __something__\n\n#include <stdio.h>\n\n#endif\n";
	write_file(fp, data, strlen(data));

}

void write_c_file(FILE *fp) {

	const char *data = "\n\n#include <stdio.h>\n\n\n\nint main(int argc, char *argv[]) {\n\n\n\treturn 0;\n\n}";
	write_file(fp, data, strlen(data));

}

int main(int argc, char *argv[]) {

	if (argc != 2)  {

		fprintf(stderr, "\n\ngcreate: Exactly 1 argument required.\nUsage: gcreate [filename]\n\n");
		return -1;
	}

	char *filename = malloc(sizeof(char) * MAX_DATA + 1);
	if (filename == NULL) {

		perror("gcreate");
		return -1;
	}

	strncpy(filename, argv[1], MAX_DATA + 1);
	FILE *f = fopen(filename, "w");

	if (f == NULL) {

		free(filename);
		fprintf(stderr, "\n\ngcreate: Couldn't open %s for writing.\nReason: %s\n\n\n", filename, strerror(errno));
		return -1;
	}

	char *ext = strtok(filename, ".");
	if (ext) ext = strtok(NULL, ".");

	if (!ext || strcmp(ext, "c") == 0)
			write_c_file(f);
	else 
			write_h_file(f);


	if (filename) free(filename);
	if (f) fclose(f);

	return 0;

}
