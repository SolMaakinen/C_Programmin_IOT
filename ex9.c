#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int find_first(const unsigned int *array, unsigned int what) {
    for (int i = 0; array[i] != 0; i++) {
        if (array[i] == what) {
            return i;
        }
    }
    return -1;
}

int main(void) {
    unsigned int arr[20];
    srand((unsigned int)time(NULL));

    // Fill first 19 elements with random numbers in range 1-20
    for (int i = 0; i < 19; i++) {
        arr[i] = rand() % 20 + 1;
    }
    arr[19] = 0; // zero as end marker

    // Print the array one number per line
    printf("Array contents:\n");
    for (int i = 0; i < 20; i++) {
        printf("%u\n", arr[i]);
    }

    // Ask user for numbers to search
    unsigned int num;
    while (1) {
        printf("Enter number to search for (0 to stop): ");
        if (scanf("%u", &num) != 1) {
            // clear input buffer if invalid
            while (getchar() != '\n');
            printf("Invalid input, try again.\n");
            continue;
        }

        if (num == 0) {
            break;
        }

        int idx = find_first(arr, num);
        if (idx >= 0) {
            printf("Found at index %d\n", idx);
        } else {
            printf("Not found\n");
        }
    }

    printf("Program stopped.\n");
    return 0;
}
