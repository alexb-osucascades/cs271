/****************************************
 * C-ploration 8 for CS 271
 * 
 * [NAME] Alexander Birrell
 * [TERM] FALL 2024
 * 
 ****************************************/
#include "symtable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


Symbol* hashArray[SYMBOL_TABLE_SIZE]; 

int hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) 
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % SYMBOL_TABLE_SIZE;
}


// name is key
// Value is addr

void symtable_insert(hack_addr addr, char *name) {

   struct Symbol *item = (struct Symbol*) malloc(sizeof(struct Symbol));
   item->name = strdup(name);  
   item->addr = addr;

   //get the hash 
   int hashIndex = hash(name);

   //move in array until an empty or deleted cell
   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->name != NULL) {
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SYMBOL_TABLE_SIZE;
   }
	
   hashArray[hashIndex] = item;
}



Symbol *symtable_find(char* name) {
   //get the hash 
   int hashIndex = hash(name);  
	
   //move in array until an empty 
   while(hashArray[hashIndex] != NULL) {
	
      if(strcmp(hashArray[hashIndex]->name, name) == 0)
         return hashArray[hashIndex]; 
			
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SYMBOL_TABLE_SIZE;
   }        
	
   return NULL;        
}

void symtable_print_labels() {
   int i = 0;    
   for(i = 0; i<SYMBOL_TABLE_SIZE; i++) {
        if(hashArray[i] != NULL){
             printf("{%s,%d}\n",hashArray[i]->name,hashArray[i]->addr);
        }
   }
} 