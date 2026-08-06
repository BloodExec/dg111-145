#include <stdio.h>
#include <math.h>
int main()
{
    // 1: Triangle
    printf("1: Triangle\n");
    for (int i = 1; i <= 5; i++) // จำนวนแถว
    {
        for (int j = 1; j <= i; j++) // จำนวน * ในแต่ละแถว
        {
            printf("*");
        }
        printf("\n");
    }

    // 2: Square (n=4)
    printf("2: Square\n");
    int n = 4;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printf("*");
        }
        printf("\n");
    }

    // 3: Diamond (n=3)
    printf("3: Diamond\n");
    n = 3;
    for (int i = 1; i <= n; i++)
    {
        // ส่วนบน
        for (int j = 1; j <= n - i; j++)
        {
            printf(" ");
        }
        for (int j = 1; j <= 2 * i - 1; j++)
        {
            printf("*");
        }
        printf("\n");
    }
    // ส่วนล่าง
    for (int i = n - 1; i >= 1; i--)
    {
        for (int j = 1; j <= n - i; j++)
        {
            printf(" ");
        }
        for (int j = 1; j <= 2 * i - 1; j++)
        {
            printf("*");
        }
        printf("\n");
    }
}