# Custom Command-Line Shell (myshell)

#### Video Demo: <https://www.youtube.com/watch?v=pWYWXD3LPuw>

#### Description:

This project is a custom UNIX-style command-line shell written entirely in C. It serves as my final capstone project for CS50x. The shell implements a complete Read-Evaluate-Print-Loop (REPL), dynamic input tokenization, and system-level process management using POSIX standard system calls.

The primary motivation behind this project was to move beyond high-level abstractions and interact directly with the operating system kernel. By building a shell from scratch, I was forced to confront the realities of dynamic memory allocation, pointer arithmetic, and process concurrency—core concepts emphasized throughout the CS50 curriculum.

### Architecture and File Structure

To maintain clean code and separation of concerns, the project avoids a monolithic design. Instead, the architecture is divided into modular components:

*   **`main.c`**: This file contains the primary Read-Evaluate-Print-Loop (REPL). It is responsible for printing the command prompt (`myshell>`), retrieving the raw string input from the user, and passing that input down the pipeline to the parser and executor.
*   **`parser.c`**: This component handles lexical analysis. It takes the raw string provided by the user and uses functions like `strtok` to slice the input into an array of distinct tokens (strings). It strips away whitespace and formats the data into the exact structure required by the `execvp` system call.
*   **`executor.c`**: This is the heart of the process management system. It evaluates the parsed tokens to determine if the user requested a built-in command or an external system program. It then executes the appropriate logic, managing process forks and parent-child synchronization.
*   **`Makefile`**: A custom build script utilizing the GCC compiler. It automates the compilation of the multiple `.c` files into a single `myshell` executable, applying strict compilation flags (`-Wall`, `-Wextra`) to enforce memory safety and code quality.
*   **`.github/workflows/ci.yml`**: A Continuous Integration/Continuous Deployment (CI/CD) pipeline configuration. Every time code is pushed to the GitHub repository, this triggers a virtual Ubuntu server to automatically compile the C code and test the executable to ensure stability.

### Core Features and Design Decisions

#### 1. Dynamic Memory Management
Because the length of a user's command is unpredictable, the shell cannot rely on static arrays. I utilized the `getline` function in `main.c` to dynamically allocate a buffer on the heap that expands automatically based on the input size. Similarly, the array of pointers used to store the parsed tokens is dynamically allocated. To prevent memory leaks—a critical requirement in C programming—I implemented strict cleanup routines. Before the shell prompts the user for the next command, or when the program terminates, the `free()` function is systematically called on both the input buffer and the token arrays.

#### 2. Process Forking and Execution
When a standard system command (such as `ls -l` or `pwd`) is entered, the shell cannot simply execute it directly, as doing so would overwrite the shell's own process image in memory, causing it to terminate immediately.

To solve this, I designed the executor to use the `fork()` system call. This clones the current process, creating an identical child process. The child process then utilizes the `execvp()` function. I specifically chose `execvp` over `execv` or `execl` because the `p` variant automatically searches the system's `PATH` environment variable for the executable, meaning the user can type `ls` instead of `/bin/ls`. While the child process replaces its memory with the new program, the parent shell uses the `wait()` system call to pause its execution, preventing the prompt from reappearing before the command has finished outputting to the terminal.

#### 3. Built-in Commands (`cd` and `exit`)
Standard child processes run in isolated environments and cannot alter the state of the parent process. If the shell attempted to execute `cd` using `fork()` and `execvp()`, the child process would change its own directory and immediately die, leaving the parent shell's working directory entirely unchanged.

To bypass this limitation, `cd` and `exit` are implemented as built-in commands. Before creating any child processes, the executor intercepts these specific strings. If `cd` is detected, the shell calls the C standard library's `chdir()` function directly within the parent process, allowing seamless filesystem navigation. If `exit` is detected, the shell breaks the infinite REPL loop, executes its final memory cleanup routines, and gracefully returns control to the host operating system.

#### 4. Automated Testing (CI/CD)
To elevate the project to professional software engineering standards, I integrated a GitHub Actions CI/CD pipeline. The pipeline provisions an `ubuntu-latest` environment, checks out the codebase, runs the `Makefile`, and verifies that the `myshell` binary is successfully generated. Furthermore, it pipes the `exit` command directly into the compiled shell. This serves as a basic automated integration test, proving that the shell can successfully boot, process a built-in command, and terminate without triggering a segmentation fault.

This project represents the culmination of my CS50x journey, proving my ability to architect, build, and deploy low-level systems software securely and efficiently.

