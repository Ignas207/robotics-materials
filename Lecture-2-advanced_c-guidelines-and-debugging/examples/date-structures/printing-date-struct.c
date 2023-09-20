#include <stdio.h>

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
    // Accesing members
    usersDate.year = 2023;
    usersDate.month = 9;
    usersDate.day = 20;

    PrintDate(usersDate);
    return 0;
}

void PrintDate(Date date)
{
    printf("The year is %d, month is %d, today is %d.\n",
            date.year,
            date.month,
            date.day);
}