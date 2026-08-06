#include <stdio.h>
#include <math.h>
int main()
{
    // 1. for loop — เหมาะสมเมื่อทราบจานวนรอบที่แน่นอน
    for (int i = 1; i <= 10; i++)
    {
        printf("%d ", i);
    }
    // 2. while loop — เช็คเงื่อนไขก่อนทำงาน (อาจไม่ทำงานเลยถ้าเงื่อนไขเป็นเท็จตั้งแต่แรก)
    int i = 1;
    while (i <= 10)
    {
        printf("%d ", i);
        i++;
    }
    // 3. do-while loop — ทำงานก่อนอย่างน้อย 1 รอบ แล้วจึงเช็คเงื่อนไข
    int a = 1;
    do
    {
        printf("%d ", a);
        a++;
    } while (a <= 10);

    //แสดงค่า sum = 55
    int sum = 0;
    for (int i = 1; i <= 10; i++)
    {
        sum += i;
    }
    printf("Sum = %d\n", sum);

    return 0;
}
