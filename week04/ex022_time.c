#include <stdio.h>
int main()
{
    // ตัวแปลเวลา
    int seconds;
    int hours;
    int minutes;
    int secs;

    // รับเวลาวินาที
    printf("Input :  ");
    scanf("%d", &seconds);

    printf("Input: %d seconds\n", seconds);
    // แปลงเวลา
    hours = seconds / 3600;
    minutes = (seconds % 3600) / 60;
    secs = seconds % 60;

    // แสดงผลลัพธ์
    printf("Output : %02d:%02d:%02d\n", hours, minutes, secs);

    return 0;
}
