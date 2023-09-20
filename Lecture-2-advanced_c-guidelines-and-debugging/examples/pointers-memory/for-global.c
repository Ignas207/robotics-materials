#include <stdio.h>

int i = 0; // Global variable

void Print();

int main(void)
{
    Print();
    for(i = 0; i < 5; i++)
    {
        printf("%d ", i);
    }
    printf("\n");
    Print();
    return 0;
}

void Print()
{
    i++;
    printf("i is %d\n", i);
}
