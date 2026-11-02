# ******************************************************************************
# Title: Shell Build Script
# Description: Automates the compilation of the C shell project.
# ******************************************************************************

myshell: src/main.c src/parser.c src/executor.c
	gcc -Wall -Wextra -o myshell src/main.c src/parser.c src/executor.c
	