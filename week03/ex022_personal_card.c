#include <stdio.h>
int main()
{
    // ประกาศและกาหนดค่าตัวแปร
    char name[50];
    int age;
    float gpa;
    char major[50];

    // รับข้อมูลจากผู้ใช้
    printf("=== Enter Data ===\n");
    printf("Name: ");
    scanf("%s", name);
    printf("Age: ");
    scanf("%d", &age);
    printf("GPA: ");
    scanf("%f", &gpa);
    printf("Major: ");
    scanf("%s", major);

    // แสดงข้อมูลที่กรอก
    printf("\n=== PERSONAL CARD ===\n");
    printf("┌─────────────────────────────┐\n");
    printf("│ Name  : %-19s │\n", name);
    printf("│ Age   : %-4d years old      │\n", age);
    printf("│ GPA   : %-19.2f │\n", gpa);
    printf("│ Major : %-19s │\n", major);
    printf("└─────────────────────────────┘\n");

    return 0;
}