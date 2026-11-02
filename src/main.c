/*
 * Title: Main REPL Loop (CS50x Capstone)
 * Description: 
 * The entry point of the custom command-line shell. This file implements the 
 * Read-Evaluate-Print-Loop (REPL) that continuously prompts the user for 
 * input, delegates tokenization, and triggers command execution until exited.
*/
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

int main(void) 
{
    char *line = NULL;
    size_t len = 0;
    char **args;
    int status = 1;

    // Loop continues as long as status is non-zero
    while (status) 
    {
        // Print the shell prompt
        printf("myshell> ");
        
        // Read a dynamic line of input from standard input (stdin)
        // If EOF (Ctrl+D) is encountered, break the loop
        if (getline(&line, &len, stdin) == -1) break;
        
        // Tokenize the raw string into an array of arguments
        args = parse_input(line);
        
        // Execute the parsed command and update the loop status
        status = execute_command(args);
        
        // Free the dynamically allocated argument array for this iteration
        free(args);
    }
    
    // Free the dynamically allocated input line buffer before exiting
    free(line);
    return 0;
}

