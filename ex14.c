#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 100
#define MAX_LEN   80          /* maximum characters per line */
#define BUFSZ     (MAX_LEN+1) /* buffer for fgets */

static void discard_remainder(FILE *fp) {
    int ch;
    while ((ch = fgetc(fp)) != EOF && ch != '\n') {
    }
}

static void chomp_newline(char *s) {
    size_t n = strlen(s);
    if (n > 0 && s[n - 1] == '\n') s[n - 1] = '\0';
}

static void to_upper_inplace(char *s) {
    unsigned char *p = (unsigned char *)s;
    while (*p) {
        *p = (unsigned char)toupper(*p);
        p++;
    }
}

static int read_line_stdin(char *buf, size_t size) {
    if (!fgets(buf, (int)size, stdin)) return 0;
    chomp_newline(buf);
    size_t n = strlen(buf);
    while (n > 0 && (buf[n-1] == ' ' || buf[n-1] == '\t' || buf[n-1] == '\r')) {
        buf[--n] = '\0';
    }
    return 1;
}

int main(void) {
    char filename[4096];
    char lines[MAX_LINES][BUFSZ];
    size_t count = 0;

    printf("Enter filename: ");
    if (!read_line_stdin(filename, sizeof(filename)) || filename[0] == '\0') {
        fprintf(stderr, "Error: empty filename.\n");
        return 1;
    }

    /* Open for reading (text mode). */
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error: could not open file \"%s\" for reading.\n", filename);
        return 1;
    }

    /* Read up to MAX_LINES lines. */
    while (count < MAX_LINES) {
        if (!fgets(lines[count], (int)sizeof(lines[count]), fp)) {
            /* EOF or read error ends reading. */
            break;
        }
        /* If the input line was longer than MAX_LEN, discard the rest. */
        if (strchr(lines[count], '\n') == NULL) {
            discard_remainder(fp);
        }
        chomp_newline(lines[count]);
        count++;
    }

    fclose(fp);

    /* Convert all read lines to upper case. */
    for (size_t i = 0; i < count; i++) {
        to_upper_inplace(lines[i]);
    }

    /* Reopen the same file for writing (text mode). */
    fp = fopen(filename, "w");
    if (!fp) {
        fprintf(stderr, "Error: could not open file \"%s\" for writing.\n", filename);
        return 1;
    }

    /* Write the lines back, one per line. */
    for (size_t i = 0; i < count; i++) {
        if (fputs(lines[i], fp) == EOF || fputc('\n', fp) == EOF) {
            fprintf(stderr, "Error: failed to write to file \"%s\".\n", filename);
            fclose(fp);
            return 1;
        }
    }

    if (fclose(fp) != 0) {
        fprintf(stderr, "Warning: failed to close file \"%s\" after writing.\n", filename);
    }

    return 0;
}