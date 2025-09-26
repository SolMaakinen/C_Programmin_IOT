#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FNAME_MAX 4096

static void strip_newline(char *s) {
    if (!s) return;
    size_t n = strlen(s);
    if (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r')) {
        s[n - 1] = '\0';
        n = strlen(s);
        if (n > 0 && s[n - 1] == '\r') s[n - 1] = '\0';
    }
}

int main(void) {
    char fname[FNAME_MAX];

    printf("Enter filename: ");
    if (!fgets(fname, sizeof(fname), stdin)) {
        fprintf(stderr, "Error: failed to read filename from stdin.\n");
        return 1;
    }
    strip_newline(fname);

    if (fname[0] == '\0') {
        fprintf(stderr, "Error: empty filename.\n");
        return 1;
    }

    FILE *fp = fopen(fname, "r");
    if (!fp) {
        fprintf(stderr, "Error: could not open file \"%s\" for reading.\n", fname);
        return 1;
    }

    long value, minv = 0, maxv = 0, count = 0;

    while (fscanf(fp, "%ld", &value) == 1) {
        if (count == 0) {
            minv = value;
            maxv = value;
        } else {
            if (value < minv) minv = value;
            if (value > maxv) maxv = value;
        }
        count++;
    }

    fclose(fp);

    if (count > 0) {
        printf("Count: %ld\n", count);
        printf("Lowest: %ld\n", minv);
        printf("Highest: %ld\n", maxv);
    } else {
        printf("Count: 0\n");
        printf("No integers were read from the file.\n");
    }

    return 0;
}