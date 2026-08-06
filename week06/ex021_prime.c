#include <stdio.h>
#include <math.h>
int main()
{
    int n;
    int isPrime = 1; // สมมติว่าเป็นจำนวนเฉพาะ

    // รับค่าจำนวนเต็มบวก
    printf("Enter a positive integer: ");
    scanf("%d", &n);

    // แสดงผลลัพธ์ว่าเป็นจำนวนเฉพาะหรือไม่
    if (n <= 1)
    {
        isPrime = 0;
    }
    else
        for (int i = 2; i < n; i++)
        {
            if (n % i == 0)
            {
                isPrime = 0;
                break;
            }
        }

    if (isPrime)
    {
        printf("%d is a Prime Number\n", n);
    }
    else
    {
        printf("%d is NOT a Prime Number (divisible by %d)\n", n, n / 2);
    }
    return 0;
}