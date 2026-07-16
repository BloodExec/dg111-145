#include <stdio.h>
int main()
{
    // ตัวแปลน้ำหนักและส่วนสูงจากผู้ใช้
    float weight;
    float height;
    float height_m;
    float bmi;

    // รับข้อมูลจากผู้ใช้
    printf("Input Weight (kg):  ");
    scanf("%f", &weight);
    printf("Input Height (cm): ");
    scanf("%f", &height);

    // แปลงส่วนสูงจาก cm → m
    height_m = height / 100.0;

    // คำนวณ BMI
    bmi = weight / (height_m * height_m);

    // ตัดสินสถานะจากค่า BMI และแสดงผลลัพธ์
    if (bmi < 18.5)
    {
        printf("OUTPUT BMI: %.2f -> Underweight\n", bmi);
    }
    else if (bmi >= 18.5 && bmi < 24.9)
    {
        printf("OUTPUT BMI: %.2f -> Normal\n", bmi);
    }
    else if (bmi >= 25 && bmi < 29.9)
    {
        printf("OUTPUT BMI: %.2f -> Overweight\n", bmi);
    }
    else
    {
        printf("OUTPUT BMI: %.2f -> Obesity\n", bmi);
    }

    return 0;
}
