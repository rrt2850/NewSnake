//
//  File: SetupWindow.c
//  Author: Robert Tetreault (rrt2850)
//
//  Description: Sets up the window for the snake game and restores everything
//               on exit.
//
// // // // // // // // // // // // // // // // // // // // // // // // // // /

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>

#define ESC 27

int width, height;

void reset_terminal() {
    printf("\e[0m"); // Reset all text attributes
    printf("\e[H");  // Move cursor to top-left
    printf("\e[2J"); // Clear screen
}

// Handles when the user exits by ctrl+c or 'q'
void handle_exit() {
    reset_terminal();

    // Restore terminal settings
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

    exit(0);
}

// Handles when the user exits by ctrl+c
void handle_sigint(int sig) {
    handle_exit();
}

int main() {
    // Set terminal into non-canonical mode
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

    // Clear screen
    printf("\e[2J");

    // Get terminal size
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    width = size.ws_col;
    height = size.ws_row;

    // Set background color to green for every cell in the terminal
    for (int i = 0; i < width * height; i++) {
        printf("\e[42m ");
    }

    // Move cursor to top-left
    printf("\e[H");

    // Set up signal handlers for SIGINT (Ctrl+C) and 'q'
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, handle_exit);

    // Move cursor based on arrow keys
    while (1) {
        int c = getchar();
        if (c == ESC) {
            // Escape sequence detected, check for arrow keys
            int c2 = getchar();
            int c3 = getchar();
            if (c2 == '[') {
                switch (c3) {
                    case 'D':
                        // Left arrow key
                        printf("\e[D");
                        break;
                    case 'C':
                        // Right arrow key
                        printf("\e[C");
                        break;
                    case 'A':
                        // Up arrow key
                        printf("\e[A");
                        break;
                    case 'B':
                        // Down arrow key
                        printf("\e[B");
                        break;
                }
            }
        }
        else if (c == 'q') {
            // Quit program on 'q' key
            handle_exit();
        }
    }

    return 0;
}
