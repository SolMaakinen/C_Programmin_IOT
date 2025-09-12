#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_numbers(const int *array, int count) {
    for (int i = 0; i < count; i++) {
        printf("%8d\n", array[i]);
    }
}

int main(void) {
    int arr[15];
    srand((unsigned int)time(NULL));

    for (int i = 0; i < 15; i++) {
        arr[i] = rand() % 1000; // random number (0-999)
    }

    print_numbers(arr, 15);
    return 0;
}
