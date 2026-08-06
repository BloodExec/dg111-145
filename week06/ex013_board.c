#include <stdio.h>
int main()
{
    int count = 1;
    int rows = 3;
    int cols = 5;
    for (int i = 1; i <= rows; i++)
    {
        printf("+");
        for (int j = 1; j <= cols; j++)
        {
            printf("---+");
        }
        printf("\n|");
        for (int j = 1; j <= cols; j++)
        {
            printf("%2d |", count++);
        }
        printf(" \n");
    }
    printf("+");
    for (int j = 1; j <= cols; j++)
    {
        printf("---+");
    }
    printf("\n");
}