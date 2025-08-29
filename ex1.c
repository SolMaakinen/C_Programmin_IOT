// ex1.c
#include <stdio.h>

static void clear_line(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}

int main(void) {
    double bus = 0.0, taxi = 0.0, money = 0.0;

    printf("Enter price of bus ticket: ");
    while (scanf("%lf", &bus) != 1 || bus < 0) {
        clear_line();
        printf("Invalid input. Enter price of bus ticket: ");
    }
    clear_line();

    printf("Enter price of taxi: ");
    while (scanf("%lf", &taxi) != 1 || taxi < 0) {
        clear_line();
        printf("Invalid input. Enter price of taxi: ");
    }
    clear_line();

    printf("How much money you have: ");
    while (scanf("%lf", &money) != 1 || money < 0) {
        clear_line();
        printf("Invalid input. How much money you have: ");
    }
    clear_line();

    for (;;) {
        printf("You have %.2f euros left.\n", money);

        if (money < bus && money < taxi) {
            printf("You need to walk. Bye\n");
            break;
        }

        printf("Do you want to take\n");
        printf("1) bus (%.2f euros)\n", bus);
        printf("2) taxi (%.2f euros)\n", taxi);
        printf("Enter your selection: ");

        int sel = 0;
        if (scanf("%d", &sel) != 1) {
            clear_line();
            printf("invalid input\n");
            continue;
        }
        clear_line();

        if (sel == 1) {
            printf("You chose bus.\n");
            if (money >= bus) {
                money -= bus;
            } else {
                printf("You don’t have enough money for bus.\n");
            }
        } else if (sel == 2) {
            printf("You chose taxi.\n");
            if (money >= taxi) {
                money -= taxi;
            } else {
                printf("You don't have enough money for taxi.\n");
            }
        } else {
            printf("Invalid selection!\n");
        }
    }

    return 0;
}
