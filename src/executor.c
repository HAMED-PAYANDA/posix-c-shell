/*
 * Title: Command Executor
 * Description: 
 * Manages process creation and system call execution. Identifies built-in 
 * commands (like 'exit' and 'cd') and uses fork() and execvp() to spawn child 
 * processes for external system commands.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

int execute_command(char **args) 
{
    // Handle empty command
    if (args[0] == NULL) 
    {
        return 1; 
    }

    // Built-in command: exit
    if (strcmp(args[0], "exit") == 0) 
    {
        return 0; 
    }

    // Built-in command: cd (Change Directory)
    if (strcmp(args[0], "cd") == 0) 
    {
        if (args[1] == NULL) 
        {
            fprintf(stderr, "myshell: expected argument to \"cd\"\n");
        } 
        else 
        {
            if (chdir(args[1]) != 0) 
            {
                perror("myshell error");
            }
        }
        return 1; // Return 1 to continue the REPL loop
    }

    // Duplicate the current process for external commands
    pid_t pid = fork();
    
    if (pid == 0) 
    {
        if (execvp(args[0], args) == -1) 
        {
            perror("myshell error");
        }
        exit(EXIT_FAILURE);
    } 
    else if (pid < 0) 
    {
        perror("myshell error");
    } 
    else 
    {
        wait(NULL);
    }
    
    return 1;
}

