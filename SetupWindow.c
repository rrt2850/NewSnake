#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define ESCAPE '\x1b'

int main() {
    // Set terminal into non-canonical mode
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

    // Get terminal dimensions
    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);

    // Clear screen
    printf("\e[2J");

    // Set background color to green for every spot in the window
    for (int i = 0; i < ws.ws_row; i++) {
        for (int j = 0; j < ws.ws_col; j++) {
            printf("\e[42m "); // Set background color and print a space
        }
        printf("\n"); // Move to next row
    }

    // Move cursor to top-left
    printf("\e[H");

    // Move cursor based on arrow keys
    while (1) {
        int c = getchar();
        if (c == ESCAPE) {
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
            printf("\e[0m"); // Reset all text attributes
            printf("\e[H");  // Move cursor to top-left
            printf("\e[2J"); // Clear screen
            break;
        }
    }

    // Restore terminal settings
    t.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

    return 0;
}
