#include <stdio.h>

int read_integer(void) {
    int num;
    while (1) {
        if (scanf("%d", &num) == 1) {
            return num;
        } else {
            printf("invalid input\n");
            // clear input buffer
            while (getchar() != '\n');
        }
    }
}

int main(void) {
    int num, count = 0;
    int sum = 0;

    while (1) {
        printf("Enter positive numbers or negative to stop: ");
        num = read_integer();
        if (num < 0) {
            break;
        }
        sum += num;
        count++;
    }

    if (count > 0) {
        double avg = (double)sum / count;
        printf("You entered %d positive numbers. ", count);
        printf("The average is: %.3f\n", avg);
    } else {
        printf("No positive numbers were entered.\n");
    }

    return 0;
}