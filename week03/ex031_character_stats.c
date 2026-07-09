#include <stdio.h>
int main()
{
    // ประกาศและกาหนดค่าตัวแปร
    char charactername[50];
    int maxhp;
    int attackpower;
    int defense;
    int level;

    // รับข้อมูลจากผู้ใช้
    printf("=== Create Character ===\n");
    printf("Character Name: ");
    scanf("%s", charactername);
    printf("Max HP: ");
    scanf("%d", &maxhp);
    printf("Attack Power: ");
    scanf("%d", &attackpower);
    printf("Defense: ");
    scanf("%d", &defense);
    printf("Level: ");
    scanf("%d", &level);

    // แสดงข้อมูลที่กรอก
    printf("=== Character Summary ===\n");
    printf("Name: %s\n", charactername);
    printf("Level: %d\n", level);
    printf("HP: %d\n", maxhp);
    printf("ATK: %d\n", attackpower);
    printf("DEF: %d\n", defense);
    return 0;
}