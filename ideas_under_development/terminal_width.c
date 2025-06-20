//Reading Terminal Width on POSIX Systems (Linux, macOS, etc.)

#include <stdio.h>
#include <sys/ioctl.h> // For ioctl, TIOCGWINSZ
#include <unistd.h>    // For STDOUT_FILENO

int main() {
    struct winsize w; // Struct to hold window size

    // Call ioctl to get the window size.
    // STDOUT_FILENO is typically the file descriptor for the terminal.
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        perror("ioctl"); // Print error if ioctl fails
        printf("Could not get terminal size. Using default or exiting.\n");
        // You might want to use a default width here, e.g., 80, or handle the error.
        return 1; // Indicate an error
    }

    // w.ws_col contains the width (number of columns)
    // w.ws_row contains the height (number of rows)
    printf("Terminal width: %d columns\n", w.ws_col);
    printf("Terminal height: %d rows\n", w.ws_row);

    // Example: Print a line of asterisks matching the terminal width
    if (w.ws_col > 0) {
        for (int i = 0; i < w.ws_col; i++) {
            putchar('*');
        }
        putchar('\n');
    }

    return 0;
}