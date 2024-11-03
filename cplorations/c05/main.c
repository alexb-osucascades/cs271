/****************************************
 * C-ploration 5 for CS 271
 * 
 * [NAME] Alexander Birrell
 * [TERM] FALL 2024
 * 
 ****************************************/
#include "parser.h"

int main(int argc, const char *argv[])
{		

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

			parse(fin);



			fclose(fin);

		}
	}
			
}


