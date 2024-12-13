/****************************************
 * Unit 6 proj for CS 271
 * 
 * [NAME] Alexander Birrell
 * [TERM] FALL 2024
 * 
 ****************************************/

#ifndef __HACK_H__
#define __HACK_H__

#include <stdint.h> 
#define NUM_PREDEFINED_SYMBOLS 23


#define MAX_NAME_LENGTH 20

typedef struct { 
    char name[MAX_NAME_LENGTH]; 
    int16_t address; 
} predefined_symbol;

typedef enum symbol_id{
	SYM_SP = 0,
	SYM_LCL = 1,
	SYM_ARG = 2,
	SYM_THIS = 3,
	SYM_THAT = 4,
	SYM_R0 = 0,
	SYM_R1 = 1,
	SYM_R2 = 2,
	SYM_R3 = 3,
	SYM_R4 = 4,
	SYM_R5 = 5,
	SYM_R6 = 6,
	SYM_R7 = 7,
	SYM_R8 = 8,
	SYM_R9 = 9,
	SYM_R10 = 10,
	SYM_R11 = 11,
	SYM_R12 = 12,
	SYM_R13 = 13,
	SYM_R14 = 14,
	SYM_R15 = 15,
	SYM_SCREEN = 16384,
	SYM_KBD = 24576

} symbol_id;

static const predefined_symbol predefined_symbols[NUM_PREDEFINED_SYMBOLS] = {
    {"R0", SYM_R0}, 
    {"R1", SYM_R1}, 
    {"R2", SYM_R2}, 
    {"R3", SYM_R3}, 
    {"R4", SYM_R4}, 
    {"R5", SYM_R5}, 
    {"R6", SYM_R6}, 
    {"R7", SYM_R7}, 
    {"R8", SYM_R8}, 
    {"R9", SYM_R9}, 
    {"R10", SYM_R10}, 
    {"R11", SYM_R11}, 
    {"R12", SYM_R12}, 
    {"R13", SYM_R13}, 
    {"R14", SYM_R14}, 
    {"R15", SYM_R15}, 
    {"SCREEN", SYM_SCREEN},
    {"KBD", SYM_KBD},
    {"SP", SYM_SP},
    {"LCL", SYM_LCL},
    {"ARG", SYM_ARG},
    {"THIS", SYM_THIS},
    {"THAT", SYM_THAT}
};

typedef enum jump_id{
	JMP_INVALID = -1,
	JMP_NULL,
	JMP_JGT,
	JMP_JEQ,
	JMP_JGE,
	JMP_JLT,
	JMP_JNE,
	JMP_JLE,
	JMP_JMP,
} jump_id;

typedef enum dest_id{
	DEST_INVALID = -1,
	DEST_NULL,
	DEST_M,
	DEST_D,
	DEST_MD,
	DEST_A,
	DEST_AM,
	DEST_AD,
	DEST_AMD,
} dest_id;

typedef enum comp_id{
	// a = 0
	COMP_INVALID = -1,
	COMP_0 = 42,
	COMP_1 = 63,
	COMP_2 = 58,
	COMP_3 = 12,
	COMP_4 = 48,
	COMP_5 = 13,
	COMP_6 = 49,
	COMP_7 = 15,
	COMP_8 = 51,
	COMP_9 = 31,
	COMP_10 = 55,
	COMP_11 = 14,
	COMP_12 = 50,
	COMP_13 = 2,
	COMP_14 = 19,
	COMP_15 = 7,
	COMP_16 = 0,
	COMP_17 = 21,
	// a = 1
	COMP_18 = 112,
	COMP_19 = 113,
	COMP_20 = 115,
	COMP_21 = 119,
	COMP_22 = 114,
	COMP_23 = 66,
	COMP_24 = 83,
	COMP_25 = 71,
	COMP_26 = 64,
	COMP_27 = 85,

} comp_id;


static inline jump_id str_to_jumpid(const char *s){
	
	jump_id id = JMP_INVALID;
	
	if (s == NULL){
		id = JMP_NULL;
	}
	else if(strcmp(s, "JGT") == 0){
		id = JMP_JGT;
	}
	else if(strcmp(s, "JEQ") == 0){
		id = JMP_JEQ;
	}
	else if(strcmp(s, "JGE") == 0){
		id = JMP_JGE;
	}
	else if(strcmp(s, "JLT") == 0){
		id = JMP_JLT;
	}
	else if(strcmp(s, "JNE") == 0){
		id = JMP_JNE;
	}
	else if(strcmp(s, "JLE") == 0){
		id = JMP_JLE;
	}
	else if(strcmp(s, "JMP") == 0){
		id = JMP_JMP;
	}

	return id;
};

static inline dest_id str_to_destid(const char *s){
	dest_id id = DEST_INVALID;
	
	if (s == NULL){
		id = DEST_NULL;
	}
	else if(strcmp(s, "M") == 0){
		id = DEST_M;
	}
	else if(strcmp(s, "D") == 0){
		id = DEST_D;
	}
	else if(strcmp(s, "MD") == 0){
		id = DEST_MD;
	}
	else if(strcmp(s, "A") == 0){
		id = DEST_A;
	}
	else if(strcmp(s, "AM") == 0){
		id = DEST_AM;
	}
	else if(strcmp(s, "AD") == 0){
		id = DEST_AD;
	}
	else if(strcmp(s, "AMD") == 0){
		id = DEST_AMD;
	}
	return id;
};




static inline comp_id str_to_compid(const char *s, int *a){
	comp_id id = COMP_INVALID;
	
	if(strcmp(s, "0") == 0){
		id = COMP_0;
		*a = 0;
	}
	else if(strcmp(s, "1") == 0){
		id = COMP_1;
		*a = 0;
	}
	else if(strcmp(s, "-1") == 0){
		id = COMP_2;
		*a = 0;
	}
	else if(strcmp(s, "D") == 0){
		id = COMP_3;
		*a = 0;
	}
	else if(strcmp(s, "A") == 0){
		id = COMP_4;
		*a = 0;
	}
	else if(strcmp(s, "!D") == 0){
		id = COMP_5;
		*a = 0;
	}
	else if(strcmp(s, "!A") == 0){
		id = COMP_6;
		*a = 0;
	}
	else if(strcmp(s, "-D") == 0){
		id = COMP_7;
		*a = 0;
	}
	else if(strcmp(s, "-A") == 0){
		id = COMP_8;
		*a = 0;
	}
	else if(strcmp(s, "D+1") == 0){
		id = COMP_9;
		*a = 0;
	}
	else if(strcmp(s, "A+1") == 0){
		id = COMP_10;
		*a = 0;
	}
	else if(strcmp(s, "D-1") == 0){
		id = COMP_11;
		*a = 0;
	}
	else if(strcmp(s, "A-1") == 0){
		id = COMP_12;
		*a = 0;
	}
	else if(strcmp(s, "D+A") == 0){
		id = COMP_13;
		*a = 0;
	}
	else if(strcmp(s, "D-A") == 0){
		id = COMP_14;
		*a = 0;
	}
	else if(strcmp(s, "A-D") == 0){
		id = COMP_15;
		*a = 0;
	}
	else if(strcmp(s, "D&A") == 0){
		id = COMP_16;
		*a = 0;
	}
	else if(strcmp(s, "D|A") == 0){
		id = COMP_17;
		*a = 0;
	}
	// a = 1
	else if(strcmp(s, "M") == 0){

		id = 48;
		*a = 1;
	}
	else if(strcmp(s, "!M") == 0){
		id = 49;
		*a = 1;
	}
	else if(strcmp(s, "-M") == 0){
		id = COMP_20;
		*a = 1;
	}
	else if(strcmp(s, "M+1") == 0){
		id = 55;
		*a = 1;
	}
	else if(strcmp(s, "M-1") == 0){
		id = 50;
		*a = 1;
	}
	else if(strcmp(s, "D+M") == 0){
		id = 2;
		*a = 1;
	}
	else if(strcmp(s, "D-M") == 0){
		id = 19;
		*a = 1;
	}
	else if(strcmp(s, "M-D") == 0){
		id = 7;
		*a = 1;
	}
	else if(strcmp(s, "D&M") == 0){
		id = 0;
		*a = 1;
	}
	else if(strcmp(s, "D|M") == 0){
		id = 21;
		*a = 1;
	}
	return id;
}


#endif