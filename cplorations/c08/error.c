/****************************************
 * C-ploration 8 for CS 271
 * 
 * [NAME] Alexander Birrell
 * [TERM] FALL 2024
 * 
 ****************************************/
#include <stdio.h>
#include "error.h"



void exit_program(enum exitcode code, ...)
{
    va_list arguments;
    va_start(arguments, code);

    printf("ERROR: ");
    vfprintf(stdout, error_messages[code], arguments);
    printf("\n");

    va_end(arguments);
    exit(code);
}