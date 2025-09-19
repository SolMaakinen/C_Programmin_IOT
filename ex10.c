#include <stdio.h>
#include <string.h>

#define MAX_INPUT 256

int main(void) {
    char input[MAX_INPUT];

    for (;;) {
        printf("Enter a string (type stop to end): ");
        if (!fgets(input, sizeof input, stdin)) {
            if (ferror(stdin)) {
                perror("Input error");
            } else {
                puts("\nEnd of input.");
            }
            break;
        }

        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[--len] = '\0';
        }

        if (len == 0) {
            continue;
        }

        printf("Length: %zu\n", len);

        if (strcmp(input, "stop") == 0) {
            break;
        }
    }

    return 0;
}