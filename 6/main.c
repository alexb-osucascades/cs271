/****************************************
 * Unit 6 proj for CS 271
 * 
 * [NAME] Alexander Birrell
 * [TERM] FALL 2024
 * 
 ****************************************/
#include "parser.h"
#include "error.h"
#include "symtable.h"
#define MAX_INSTRUCTION_COUNT 30000

int main(int argc, const char *argv[])
{
	instruction *instructions = malloc(MAX_INSTRUCTION_COUNT * sizeof(instruction));		

	if (argc != 2) {
		// incorrect number of arguments
			exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);         

	} else {
		FILE *fin = fopen(argv[1], "r" );

		if(fin == NULL){ 
			exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
		

		} else {

			int num_instructions = parse(fin, instructions);
			assemble(argv[1], instructions, num_instructions);
			

			//symtable_print_labels();

			fclose(fin);
			

		}
	}

	free(instructions);
			
}


