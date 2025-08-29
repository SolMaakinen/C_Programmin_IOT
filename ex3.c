// ex3.c
#include <stdio.h>
#include <stdlib.h>

static void clear_line(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}

int main(void) {
    int n = 0;

    printf("How many students: ");
    while (scanf("%d", &n) != 1 || n <= 0) {
        clear_line();
        printf("Invalid input. How many students: ");
    }
    clear_line();

    int *grades = (int*)malloc((size_t)n * sizeof(int));
    if (!grades) {
        fprintf(stderr, "Allocation failed.\n");
        return 1;
    }
    for (int i = 0; i < n; ++i) grades[i] = -1; // initialize to -1

    for (;;) {
        int s = 0;
        printf("Enter student number (1 - %d) or 0 to stop: ", n);
        if (scanf("%d", &s) != 1) {
            clear_line();
            printf("invalid input\n");
            continue;
        }
        clear_line();

        if (s == 0) break;

        if (s < 1 || s > n) {
            printf("Invalid student number!\n");
            continue;
        }

        for (;;) {
            int g;
            printf("Enter grade (0 - 5) for student %d or -1 to cancel: ", s);
            if (scanf("%d", &g) != 1) {
                clear_line();
                printf("invalid input\n");
                continue;
            }
            clear_line();

            if (g == -1) {
                // do not change existing grade
                break;
            }
            if (g < 0 || g > 5) {
                printf("Invalid grade!\n");
                continue;
            }
            grades[s - 1] = g;
            break;
        }
    }

    printf("Student Grade\n");
    for (int i = 0; i < n; ++i) {
        if (grades[i] == -1)
            printf("%d N/A\n", i + 1);
        else
            printf("%d %d\n", i + 1, grades[i]);
    }

    free(grades);
    return 0;
}
