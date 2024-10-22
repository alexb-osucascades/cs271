/****************************************
 * C-ploration 3 for CS 271
 * 
 * [NAME] Alexander Birrell
 * [TERM] FALL 2024
 * 
 ****************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 




int main(int argc, const char *argv[])
{	

	#define MAX_LINE_LENGTH  200

	if (argc < 2){
	printf("Usage: %s [filename]\n", argv[0]);
	exit(EXIT_FAILURE);
	return 1;

	} else {
		FILE *fin = fopen(argv[1], "r" );

		if (fin == NULL){
			perror("Unable to open file!");
			exit(EXIT_FAILURE);

		} else {

			char out_file[MAX_LINE_LENGTH];

			strcpy(out_file, argv[1]);
			strcat(out_file, ".echo");

			FILE *fout = fopen(out_file, "w+" );

			char line[MAX_LINE_LENGTH] = {0};
			unsigned int line_num = 0;

			while (fgets(line, sizeof(line), fin))  {
				line_num++;
				printf("[%04d] %s", line_num, line);
				fprintf(fout, "%s", line);

			}
			fclose(fin);
			fclose(fout);

		}
	}
}
