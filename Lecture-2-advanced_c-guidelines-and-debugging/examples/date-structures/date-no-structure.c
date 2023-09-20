#include <stdio.h>

int GetNumber(void);

int main(void)
{
    int year;
    int month;
    int day;
    
    year = GetNumber();
    month = GetNumber();
    day = GetNumber();

    printf("The year is %d, month is %d and day is %d!\n", year, month, day);
    return 0;
}

int GetNumber(void)
{
    int number = 0;
    printf("Enter the number: ");
    scanf("%d", &number);
    return number;
}
