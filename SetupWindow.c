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


void set_terminal(int width, int height) {
    // Set terminal into non-canonical mode
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

    // Clear screen
    printf("\e[2J");

    // Set background color to green for every cell in the terminal
    for (int i = 0; i < width * height; i++) {
        printf("\e[42m ");
    }

    // Move cursor to top-left
    printf("\e[H");
}

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


