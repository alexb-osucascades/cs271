/****************************************
 * C-ploration 8 for CS 271
 * 
 * [NAME] Alexander Birrell
 * [TERM] FALL 2024
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s){	


	char s_new[strlen(s)+1];
	int i = 0;

	for (char *s2 = s; *s2; s2++) { 
		if (*s2 == '/' && *(s2+1) == '/') {
			break;
		}
		else if (!(isspace(*s2))){
			s_new[i++] = *s2;
		}
	}
	s_new[i] = '\0';
	strcpy(s, s_new);

    return s;	
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
void parse(FILE * file){
	
		char line[MAX_LINE_LENGTH] = {0};
		char inst_type;
		char label[MAX_LABEL_LENGTH];
		int i = 0;
		unsigned int line_num = 0;
		unsigned int instr_num = 0;


		while (fgets(line, sizeof(line), file))  {

			line_num++;
			
			if (instr_num > MAX_INSTRUCTIONS) {
				exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
			}

			strip(line);
			if (!(*line)){
				continue;
			}
			
			if (is_Atype(line)) {
				inst_type = 'A';
				i++;
			}
			else if (is_label(line)) {
				inst_type = 'L';
				extract_label(line, label);

				if (!(isalpha(label[0]))) {
					exit_program(EXIT_INVALID_LABEL, line_num, label);

				}
				if (symtable_find(label) != NULL) {
					exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, label);
				}
				strcpy(line, label);
				// Make i var counter
				// if line is NOT a label, increment
				// if line IS a label, do not increment and use this addr in symtable_insert
				symtable_insert(instr_num, label);
				continue;

			}
			else if (is_Ctype(line)) {
				inst_type = 'C';
				i++;
			}
			else {
				inst_type = ' ';
				i++;
			}

			printf("%u: %c  %s\n", instr_num, inst_type, line);
			instr_num++;
		}

}


bool is_Atype(const char *line) {

	if (line[0] == '@') {
		return true;
	}
	else {
		return false;
	}

}

bool is_label(const char *line) {

	if ((line[0] == '(') && (line[strlen(line) - 1] == ')')) {
		return true;
	}
	else {
		return false;
	}

}

bool is_Ctype(const char *line) {

	if (!(is_Atype(line)) && !(is_label(line))) {
		return true;
	}
	else {
		return false;
	}
}

char *extract_label(const char *line, char* label) {

	char line_new[strlen(line)+1];
	int i = 0;

	for (char *line2 = line; *line2; line2++) { 
		if (*line2 != '(' && *line2 != ')'){ 
			line_new[i++] = *line2;
		}
	}
	line_new[i] = '\0';
	strcpy(label, line_new);

    return label;	

}