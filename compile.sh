#!/bin/bash

# Compile SetupWindow.c to create SetupWindow.o
gcc -c SetupWindow.c

# Compile Snake.c to create Snake.o
gcc -c Snake.c

# Link SetupWindow.o and Snake.o to create the executable file Snake
gcc -o Snake Snake.o SetupWindow.o
