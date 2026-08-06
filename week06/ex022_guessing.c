#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    int number, guess, attempts = 0;
    srand(time(NULL));         // สุ่มตัวเลขใหม่ทุกครั้งที่รันโปรแกรม
    number = rand() % 100 + 1; // สุ่มตัวเลขระหว่าง 1 ถึง 100

    printf("Number Guessing Game (1-100)\n");

    do
    {
        printf("Enter your guess: ");
        scanf("%d", &guess);
        attempts++;

        if (guess < number)
        {
            printf("Too low! \n");
        }
        else if (guess > number)
        {
            printf("Too high! \n");
        }
        else
        {
            printf("Correct! You guessed it in %d attempts.\n", attempts);
        }
    } while (guess != number);

    return 0;
}