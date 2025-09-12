#include <stdio.h>
#include <stdbool.h>

bool read_positive(int *value) {
    int temp;
    if (scanf("%d", &temp) == 1) {
        if (temp > 0) {
            *value = temp;
            return true;
        }
    } else {
        // clear input buffer if scanf failed
        while (getchar() != '\n');
    }
    return false;
}

int main(void) {
    int guess;
    int fails = 0;

    while (fails < 3) {
        printf("Guess how much money I have!\n");
        printf("Enter a positive number: ");

        if (read_positive(&guess)) {
            printf("You didn't get it right. I have %d euros.\n", guess * 2 + 20);
        } else {
            printf("Incorrect input\n");
            fails++;
        }
    }

    printf("I give up! See you later!\n");
    return 0;
}
