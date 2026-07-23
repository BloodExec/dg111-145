#include <stdio.h>
#include <math.h>
int main()
{
    int day;

    // รับค่าวัน
    printf("Enter a day (1-7): ");
    scanf("%d", &day);

    switch (day)
    {
    case 1:
        printf("%d -> Monday (Weekday)\n", day);
        break;
    case 2:
        printf("%d -> Tuesday (Weekday)   \n", day);
        break;
    case 3:
        printf("%d -> Wednesday (Weekday)\n", day);
        break;
    case 4:
        printf("%d -> Thursday (Weekday)\n", day);
        break;
    case 5:
        printf("%d -> Friday (Weekday)\n", day);
        break;
    case 6:
        printf("%d -> Saturday (Weekend!  🎉)\n", day);
        break;
    case 7:
        printf("%d -> Sunday (Weekend!  🎉)\n", day);
        break;
    default:
        printf("%d -> Invalid input\n", day);
    };

    return 0;
}