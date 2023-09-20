#include <stdio.h>

int main(void)
{
    int number = 123456;
    char text[] = "Hello\n";
    for(int i = 0; i < 5; i++)
    {
        printf("%d ", i);
    }
    // We can't do this!
    // printf("%d ", i);
    return 0;
}
