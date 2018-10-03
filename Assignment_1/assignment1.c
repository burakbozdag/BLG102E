#include <stdio.h> // printf, scanf
#include <stdlib.h> // EXIT_SUCCESS

int main()
{
    int year = 0, month = 0, day = 0, end_year = 0;
    printf("Enter date [year month day]: ");
    scanf("%d %d %d", &year, &month, &day);
    int actual_year = year;
    switch (month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        if (day > 31) {
            printf("Invalid date.\n");
            return EXIT_FAILURE;
        }
        break;
    case 2:
        if (day > 28) {
            printf("Invalid date.\n");
            return EXIT_FAILURE;
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        if (day > 30) {
            printf("Invalid date.\n");
            return EXIT_FAILURE;
        }
        break;
    }
    printf("Enter end year: ");
    scanf("%d", &end_year);

    if (month == 1 || month == 2) {
        month += 12;
        year--;
    }

    int q = day, m = month, j = (year - (year % 100)) / 100, k = year % 100;

    // Zeller's congruence: (q + (13 * (m + 1) / 5) + k + (k / 4) + (j / 4) + (5 * j)) % 7

    int result_day = (q + (13 * (m + 1) / 5) + k + (k / 4) + (j / 4) + (5 * j)) % 7;
    switch (result_day) {
    case 0:
        printf("It's a Saturday.\n");
        break;
    case 1:
        printf("It's a Sunday.\n");
        break;
    case 2:
        printf("It's a Monday.\n");
        break;
    case 3:
        printf("It's a Tuesday.\n");
        break;
    case 4:
        printf("It's a Wednesday.\n");
        break;
    case 5:
        printf("It's a Thursday.\n");
        break;
    case 6:
        printf("It's a Friday.\n");
        break;
    }

    int counter = 0;
    for (int i = year + 1; i <= end_year; i++) {
        int j = (i - (i % 100)) / 100;
        int k = i % 100;
        int result = (q + (13 * (m + 1) / 5) + k + (k / 4) + (j / 4) + (5 * j)) % 7;
        if (result == result_day) {
            counter++;
        }
    }
    printf("Same day-and-month on same weekday between %d and %d: %d\n", actual_year + 1, end_year, counter);

    return EXIT_SUCCESS;
}
