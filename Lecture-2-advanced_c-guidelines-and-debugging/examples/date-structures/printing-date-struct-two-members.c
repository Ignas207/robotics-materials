#include <stdio.h>

#define PRINT_DAVES_DATE

// Struct definition
typedef struct 
{
    int year;
    int month;
    int day;
} Date;

void PrintDate(Date date);

int main(void)
{
    // Struct creation
    Date usersDate;

#ifdef PRINT_DAVES_DATE
    Date davesDate;
#endif

    // Accessing struct members
    usersDate.year = 2023;
    usersDate.month = 9;
    usersDate.day = 20;

#ifdef PRINT_DAVES_DATE
    davesDate.year = 1990;
    davesDate.month = 11;
    davesDate.day = 14;
#endif

    // Passing a structure
    PrintDate(usersDate);

#ifdef PRINT_DAVES_DATE
    PrintDate(davesDate);
#endif

    return 0;
}

void PrintDate(Date date)
{
    printf("The year is %d, month is %d, today is %d.\n",
            date.year,
            date.month,
            date.day);
}
