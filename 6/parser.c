/****************************************
 * Unit 6 proj for CS 271
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
int parse(FILE * file, instruction *instructions){
	
		char line[MAX_LINE_LENGTH] = {0};
		char inst_type;
		char label[MAX_LABEL_LENGTH];
		int i = 0;
		unsigned int line_num = 0;
		unsigned int instr_num = 0;
		instruction instr;

		add_predefined_symbols();
		//symtable_print_labels();

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
				if (!parse_A_instruction(line, &instr.a_instr)){
					exit_program(EXIT_INVALID_A_INSTR, line_num, line);
				}
				instr.type = A_type;
				if (instr.a_instr.is_addr) { 
					printf("A: %d\n", instr.a_instr.address); 
				} 
				else { 
					printf("A: %s\n", instr.a_instr.label); 
					}
				
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

				char tmp_line[MAX_LINE_LENGTH];
				strcpy(tmp_line, line);

				// Parse C instruction
				parse_C_instruction(tmp_line, &instr.c_instr);

				// Check for invalid fields in the C instruction
				if (instr.c_instr.dest == -1) {
					exit_program(EXIT_INVALID_C_DEST, line_num, line);
				}
				else if (instr.c_instr.comp == -1) {
					exit_program(EXIT_INVALID_C_COMP, line_num, line);
				}
				else if (instr.c_instr.jump == -1) {
					exit_program(EXIT_INVALID_C_JUMP, line_num, line);
				}
				 
				else {
				instr.type = C_type;
				printf("C: d=%d, c=%d, j=%d\n", instr.c_instr.dest, instr.c_instr.comp, instr.c_instr.jump);

				}

			} 
			//printf("%u: %c  %s\n", instr_num, inst_type, line);
			instructions[instr_num++] = instr;
		}
	return instr_num;
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

void add_predefined_symbols() {
    for (int i = 0; i < NUM_PREDEFINED_SYMBOLS; ++i) {
        predefined_symbol symbol = predefined_symbols[i];
        symtable_insert(symbol.address, symbol.name);
    }
}



bool parse_A_instruction(const char *line, a_instruction *instr) {
    char *s = (char *)malloc(strlen(line));
    strcpy(s, line + 1);
    char *s_end = NULL;
    long result = strtol(s, &s_end, 10);
    if (s == s_end) {
        instr->label = (char *)malloc(strlen(line));
        strcpy(instr->label, s);
        instr->is_addr = false;
    }
    else if (*s_end != 0) {
        return false;
    }
    else {
        instr->address = (int16_t)result;
        instr->is_addr = true;
    }

    return true;
}



void parse_C_instruction(char *line, c_instruction *instr) {
	//printf("GOT HERE");

	//Change all of these (except a) to default (-1)
    instr->jump = JMP_INVALID;
    instr->comp = COMP_INVALID;
    instr->dest = DEST_INVALID;
	instr->a = 0;

	char line_copy[MAX_LINE_LENGTH];
	strcpy(line_copy, line);
	line_copy[MAX_LINE_LENGTH - 1] = '\0';

    // Tokenize the line 
	char *temp = strtok(line_copy, ";");
	char *jump_part = strtok(NULL, ";");


    // Tokenize the temp value 
	char *dest_part = strtok(temp, "=");
	char *comp_part = strtok(NULL, "=");

    // If comp is NULL, dest_part is actually comp and dest is NULL
	if(comp_part == NULL){
		comp_part = dest_part;
		dest_part = NULL;
	}

    // Set jump, comp, dest, and a
	int a_bit = 0;
	instr->comp = str_to_compid(comp_part, &a_bit);
	instr->dest = dest_part ? str_to_destid(dest_part) : DEST_NULL;
	instr->jump = jump_part ? str_to_jumpid(jump_part) : JMP_NULL;
	instr->a = a_bit;
}

