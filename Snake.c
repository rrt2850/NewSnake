#include "SetupWindow.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>

#define ESC 27

int width, height;

int main() {
    // Get terminal size
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    width = size.ws_col;
    height = size.ws_row;

    set_terminal();

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
