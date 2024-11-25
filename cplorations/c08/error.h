#ifndef __ERROR_H__
#define __ERROR_H__#
#include <stdarg.h>


enum exitcode {
    /*
    * Error code 1 represents that given file does not exist.
    */
    EXIT_INCORRECT_ARGUMENTS = 1,
    EXIT_CANNOT_OPEN_FILE = 2,
    EXIT_TOO_MANY_INSTRUCTIONS = 3,
    EXIT_INVALID_LABEL = 4,
    EXIT_SYMBOL_ALREADY_EXISTS = 5,

}; 

const char *error_messages[] =
{
    [EXIT_INCORRECT_ARGUMENTS] = "Usage: %s [filename]",
    [EXIT_CANNOT_OPEN_FILE] = "Cannot open file %s",
    [EXIT_TOO_MANY_INSTRUCTIONS] = "File contains more than the maximum of %u instructions.",
    [EXIT_INVALID_LABEL] = "Line %u: %s : Invalid label name.",
    [EXIT_SYMBOL_ALREADY_EXISTS] = "Line %u: %s : Symbol is already defined."
};

void exit_program(enum exitcode code, ...);




#endif