#ifndef __SYMTABLE_H__
#define __SYMTABLE_H__

#include <stdint.h> 

typedef int16_t hack_addr;

#define SYMBOL_TABLE_SIZE 1000


typedef struct Symbol { 
    char *name; 
    hack_addr addr; 
} Symbol;


int hash(char *str);
struct Symbol *symtable_find(char * name);
void symtable_insert(hack_addr addr, char * name);
void symtable_display_table();
void symtable_print_labels();

#endif