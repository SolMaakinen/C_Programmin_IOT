#include <stdio.h>

int read_range(int low, int high) {
    int num;
    int ch;
    while (1) {
        printf("Enter a number between %d and %d: ", low, high);
        if (scanf("%d", &num) == 1) {
            if (num >= low && num <= high) {
                return num;
            } else {
                printf("Number not in range, try again.\n");
            }
        } else {
            printf("Invalid input, try again.\n");
        }
        // clear
        while ((ch = getchar()) != '\n' && ch != EOF) { }
    }
}

int main(void) {
    printf("Let's play!\n");

    for (int round = 0; round < 3; round++) {
        printf("Roll a die and enter your result.\n");
        int user = read_range(1, 6);

        if (user == 6) {
            printf("I got 6. It is a tie!\n");
        } else {
            printf("I got %d. I win!\n", user + 1);
        }
    }

    printf("Better luck next time. Bye!\n");
    return 0;
}