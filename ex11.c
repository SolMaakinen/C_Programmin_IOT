#include <stdio.h>
#include <string.h>

#define MAX_TEXT 256
#define MAX_REPL 16

int replace_char(char *str, const char *repl) {
    if (!str || !repl) return 0;
    if (repl[0] == '\0' || repl[1] == '\0') return 0;

    char from = repl[0];
    char to   = repl[1];
    int count = 0;

    for (char *p = str; *p != '\0'; ++p) {
        if (*p == from) {
            *p = to;
            ++count;
        }
    }
    return count;
}

static void strip_newline_cr(char *s) {
    size_t n = strlen(s);
    while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r')) {
        s[--n] = '\0';
    }
}

int main(void) {
    char text[MAX_TEXT];
    char repl[MAX_REPL];

    printf("Enter text (max %d chars): ", MAX_TEXT - 1);
    if (!fgets(text, sizeof text, stdin)) {
        if (ferror(stdin)) perror("Input error");
        return 1;
    }
    strip_newline_cr(text);

    printf("Enter two characters: the first is what to replace, the second is the new character (e.g., a9): ");
    if (!fgets(repl, sizeof repl, stdin)) {
        if (ferror(stdin)) perror("Input error");
        return 1;
    }
    strip_newline_cr(repl);


    if (repl[0] == '\0' || repl[1] == '\0' || repl[2] != '\0') {
        puts("Replacement must be exactly two characters.");
        return 1;
    }

    int count = replace_char(text, repl);

    if (count > 0) {
        printf("Replaced %d characters.\n", count);
        printf("Modified string: %s\n", text);
    } else {
        puts("String was not modified.");
    }
    return 0;
}
