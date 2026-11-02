# Custom Command-Line Shell (myshell)
#### Video Demo:  <[INSERT_YOUTUBE_URL_HERE](https://www.youtube.com/watch?v=pWYWXD3LPuw)>
#### Description:

This project is a custom UNIX-style command-line shell written entirely in C. It serves as my final capstone project for CS50x. The shell implements a complete Read-Evaluate-Print-Loop (REPL), dynamic input tokenization, and system-level process management using POSIX standard system calls.

## Architecture and File Structure

To maintain a clean and scalable codebase, the project is divided into distinct modular files:

*   **`src/shell.h`**: The central header file declaring all shared constants (like `MAX_ARGS`) and function prototypes. It links the separate C modules together.
*   **`src/main.c`**: Houses the core REPL loop. It continuously prompts the user (`myshell> `), dynamically reads standard input using `getline()`, and orchestrates the parsing and execution phases.
*   **`src/parser.c`**: Responsible for lexical analysis. It uses `strtok()` to slice the raw user input string into a null-terminated array of tokens (arguments) that can be safely passed to system execution functions.
*   **`src/executor.c`**: Manages process spawning and built-in commands. It intercepts commands that must modify the shell's own state (like `cd` using `chdir()` and `exit`), and utilizes `fork()` and `execvp()` to spawn child processes for all other standard system commands (e.g., `ls`, `pwd`, `mkdir`).
*   **`Makefile`**: A custom build script that compiles the source files using `gcc` with strict warning flags (`-Wall -Wextra`) to ensure memory safety and clean execution.

## Design Choices

I chose C for this project to deeply explore low-level memory management and operating system interactions. 

One of the primary challenges was handling memory dynamically. Because a user's input length is unpredictable, `getline()` was used to allocate memory on the fly, which then required careful tracking to `free()` the memory at the end of each loop iteration to prevent leaks. 

Additionally, separating the logic into `parser.c` and `executor.c` rather than writing a single monolithic file ensures that the tokenization logic remains completely independent from the process-spawning logic. This modularity makes it significantly easier to add new built-in commands or swap out the parsing engine in the future.

## Usage

To compile the shell natively:
```bash
make
```
