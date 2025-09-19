#include <stdio.h>
#include <string.h>

#define MAX_TEXT 512
#define MAX_WORD 128

static void strip_newline_cr(char *s) {
    size_t n = strlen(s);
    while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r')) {
        s[--n] = '\0';
    }
}

int count_words(const char *str, const char *word) {
    if (!str || !word) return 0;
    size_t wlen = strlen(word);
    if (wlen == 0) return 0;

    int count = 0;
    const char *p = str;

    while ((p = strstr(p, word)) != NULL) {
        ++count;
        p += wlen;
    }
    return count;
}

int main(void) {
    char text[MAX_TEXT];
    char word[MAX_WORD];

    for (;;) {
        printf("Enter a string (max %d chars): ", MAX_TEXT - 1);
        if (!fgets(text, sizeof text, stdin)) {
            if (ferror(stdin)) perror("Input error");
            else puts("\nEnd of input.");
            break;
        }
        strip_newline_cr(text);

        printf("Enter a word to count (type stop to end): ");
        if (!fgets(word, sizeof word, stdin)) {
            if (ferror(stdin)) perror("Input error");
            else puts("\nEnd of input.");
            break;
        }
        strip_newline_cr(word);

        if (strcmp(word, "stop") == 0) {
            puts("Stopping.");
            break;
        }

        int n = count_words(text, word);
        printf("Occurrences: %d\n", n);
    }
    return 0;
}