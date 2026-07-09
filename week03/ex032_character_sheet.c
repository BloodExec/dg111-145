#include <stdio.h>
int main()
{
    // ประกาศและกาหนดค่าตัวแปร
    char charactername[50];
    int maxhp;
    int attackpower;
    int defense;
    int level;
    int powerscore;

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
    printf("=== CHARACTER SHEET ===\n");
    printf("╔═════════════════════════════════════╗\n");
    printf("║ Name: %-29s ║\n", charactername);
    printf("╠═════════════════════════════════════╣\n");
    printf("║ Level: %-28d ║\n", level);
    printf("║ HP: %d/%-27d ║\n", maxhp, maxhp);
    printf("║ ATK: %-30d ║\n", attackpower);
    printf("║ DEF: %-30d ║\n", defense);
    printf("╠═════════════════════════════════════╣\n");
    printf("║ HP bar: %-47s ║\n", "[██████████] 100%");
    powerscore = (attackpower * 2 + defense + maxhp / 10);
    printf("║ Power Score: %-22d ║\n", powerscore);
    printf("╚═════════════════════════════════════╝\n");
    return 0;
}