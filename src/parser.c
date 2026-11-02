/*
 * Title: Input Parser
 * Description: 
 * Handles the lexical analysis of the raw string inputted by the user. 
 * Slices the string into discrete tokens (commands and arguments) using 
 * standard whitespace delimiters.
 */
#include <stdlib.h>
#include <string.h>
#include "shell.h"

char **parse_input(char *line) 
{
    int position = 0;
    
    // Allocate memory for an array of string pointers
    char **tokens = malloc(MAX_ARGS * sizeof(char*));
    char *token;

    // Extract the first token by splitting at spaces, tabs, and newlines
    token = strtok(line, " \t\r\n\a");
    
    // Continue extracting tokens until the end of the string is reached
    while (token != NULL) 
    {
        tokens[position] = token;
        position++;
        
        // Pass NULL to strtok to continue parsing the original string
        token = strtok(NULL, " \t\r\n\a");
    }
    
    // The execvp system call requires the argument array to be NULL-terminated
    tokens[position] = NULL;
    
    return tokens;
}

