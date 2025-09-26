#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ITEMS 40
#define NAME_MAX  50
#define LINE_BUF  512

typedef struct menu_item_ {
    char name[NAME_MAX];
    double price;
} menu_item;

/* Discard rest of an overlong input line */
static void discard_remainder(FILE *fp) {
    int ch;
    while ((ch = fgetc(fp)) != EOF && ch != '\n') {
        /* discard */
    }
}

/* Trim leading and trailing spaces */
static void trim(char *s) {
    size_t n, i = 0;
    if (!s) return;
    n = strlen(s);
    while (n > 0 && (s[n-1] == ' ' || s[n-1] == '\t' || s[n-1] == '\r' || s[n-1] == '\n'))
        s[--n] = '\0';
    while (s[i] == ' ' || s[i] == '\t') i++;
    if (i > 0) memmove(s, s + i, strlen(s + i) + 1);
}

static int read_line_stdin(char *buf, size_t size) {
    if (!fgets(buf, (int)size, stdin)) return 0;
    trim(buf);
    return 1;
}

int main(void) {
    char filename[4096];
    FILE *fp;
    char line[LINE_BUF];
    menu_item items[MAX_ITEMS];
    size_t count = 0;
    unsigned long lineno = 0;

    printf("Enter filename: ");
    if (!read_line_stdin(filename, sizeof(filename)) || filename[0] == '\0') {
        fprintf(stderr, "Error: empty filename.\n");
        return 1;
    }

    fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error: could not open file \"%s\" for reading.\n", filename);
        return 1;
    }

    while (count < MAX_ITEMS) {
        if (!fgets(line, sizeof(line), fp)) {
            /* EOF or read error */
            break;
        }
        lineno++;

        /* If the input line did not include '\n', discard the remainder of the physical line. */
        if (strchr(line, '\n') == NULL) {
            discard_remainder(fp);
        }

        /* Parse "name; price" */
        char *semi = strchr(line, ';');
        if (!semi) {
            /* No semicolon = skip malformed line */
            fprintf(stderr, "Warning: line %lu has no semicolon, skipping.\n", lineno);
            continue;
        }

        *semi = '\0';
        char *name = line;
        char *price_str = semi + 1;

        trim(name);
        trim(price_str);

        if (name[0] == '\0' || price_str[0] == '\0') {
            fprintf(stderr, "Warning: line %lu missing name or price, skipping.\n", lineno);
            continue;
        }

        /* Convert price with strtod */
        char *endptr = NULL;
        double price = strtod(price_str, &endptr);

        /* Skip trailing spaces/tabs after number */
        while (endptr && (*endptr == ' ' || *endptr == '\t' || *endptr == '\r' || *endptr == '\n')) {
            endptr++;
        }
        if (endptr && *endptr != '\0') {
            fprintf(stderr, "Warning: line %lu price not a valid number, skipping.\n", lineno);
            continue;
        }

        /* Store item; truncate name if too long. */
        strncpy(items[count].name, name, NAME_MAX - 1);
        items[count].name[NAME_MAX - 1] = '\0';
        items[count].price = price;
        count++;
    }

    if (fclose(fp) != 0) {
        fprintf(stderr, "Warning: failed to close file \"%s\" after reading.\n", filename);
    }

    /* Print results: price in 8-wide field with 2 decimals, followed by name. */
    for (size_t i = 0; i < count; i++) {
        printf("%8.2f %s\n", items[i].price, items[i].name);
    }

    return 0;
}