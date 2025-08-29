// ex2.c
#include <stdio.h>

#define MONTHS 12

static void clear_line(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}

int main(void) {
    double rate_low = 0.0;     // lower tax percentage
    double rate_high = 0.0;    // higher tax percentage
    double limit = 0.0;        // yearly income limit for low tax

    double income[MONTHS] = {0};
    double tax[MONTHS] = {0};

    // Input tax rates and limit
    printf("Enter tax rate: ");
    while (scanf("%lf", &rate_low) != 1 || rate_low < 0) {
        clear_line();
        printf("Invalid input. Enter tax rate: ");
    }
    clear_line();

    printf("Enter income limit: ");
    while (scanf("%lf", &limit) != 1 || limit < 0) {
        clear_line();
        printf("Invalid input. Enter income limit: ");
    }
    clear_line();

    printf("Enter tax rate for income over the limit: ");
    while (scanf("%lf", &rate_high) != 1 || rate_high < 0) {
        clear_line();
        printf("Invalid input. Enter tax rate for income over the limit: ");
    }
    clear_line();

    // Input 12 monthly incomes
    for (int i = 0; i < MONTHS; ++i) {
        printf("Enter income for month %d: ", i + 1);
        while (scanf("%lf", &income[i]) != 1 || income[i] < 0) {
            clear_line();
            printf("Invalid input. Enter income for month %d: ", i + 1);
        }
        clear_line();
    }

    // Calculate tax month by month
    double total_income_so_far = 0.0;
    for (int i = 0; i < MONTHS; ++i) {
        double remaining_low_band = limit - total_income_so_far;
        if (remaining_low_band < 0) remaining_low_band = 0;

        double low_part = (income[i] < remaining_low_band) ? income[i] : remaining_low_band;
        double high_part = income[i] - low_part;
        if (high_part < 0) high_part = 0;

        tax[i] = low_part * (rate_low / 100.0) + high_part * (rate_high / 100.0);

        total_income_so_far += income[i];
    }

    // Print results with aligned columns
    printf("%6s %10s %10s\n", "month", "income", "tax");
    for (int i = 0; i < MONTHS; ++i) {
        printf("%6d %10.2f %10.2f\n", i + 1, income[i], tax[i]);
    }

    return 0;
}