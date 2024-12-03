/****************************************
 * C-ploration 9 for CS 271
 * 
 * [NAME] Alexander Birrell
 * [TERM] FALL 2024
 * 
 ****************************************/
#include "parser.h"
#include "error.h"
#include "symtable.h"

int main(int argc, const char *argv[])
{		

	if (argc != 2) {
		// incorrect number of arguments
			exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);         

	} else {
		FILE *fin = fopen(argv[1], "r" );

		if(fin == NULL){ 
			exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
		

		} else {

			parse(fin);

			symtable_print_labels();

			fclose(fin);

		}
	}
			
}


