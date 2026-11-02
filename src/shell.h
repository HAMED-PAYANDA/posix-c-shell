/*
 * Title: Shell Header
 * Description: 
 * Declares the constants and function prototypes for the custom shell.
 * Acts as the central linkage point for all C source modules in the project.
*/
#ifndef SHELL_H
#define SHELL_H

// Defines the maximum number of arguments a user can pass in a single command
#define MAX_ARGS 64

// Function prototypes
char **parse_input(char *line);
int execute_command(char **args);

#endif
