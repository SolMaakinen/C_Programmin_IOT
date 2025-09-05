#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int read_range(int low, int high) {
    int num;
    int ch;
    while (1) {
        if (scanf("%d", &num) == 1) {
            if (num >= low && num <= high) {
                return num;
            } else {
                printf("Error: Number not in range (%d-%d).\n", low, high);
            }
        } else {
            printf("Error: Invalid input.\n");
        }
        // clear
        while ((ch = getchar()) != '\n' && ch != EOF) { }
    }
}

int roll_die(int sides) {
    return rand() % sides + 1;
}

int main(void) {
    srand((unsigned int)time(NULL)); // seed RNG

    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Roll D6\n");
        printf("2. Roll D10\n");
        printf("3. Quit\n");
        printf("Choose an option: ");

        choice = read_range(1, 3);

        if (choice == 1) {
            printf("You rolled: %d\n", roll_die(6));
        } else if (choice == 2) {
            printf("You rolled: %d\n", roll_die(10));
        } else if (choice == 3) {
            printf("Shutting down\n");
            break;
        }
    }
    return 0;
}