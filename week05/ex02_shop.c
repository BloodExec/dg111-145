#include <stdio.h>
#include <math.h>
int main()
{
    int item;
    int price;
    int gold = 1000;
    int remaining_gold;
    int bonus;

    // หน้าต่างร้านค้า
    printf("=== ITEM SHOP ===\n");
    printf("Gold: %d\n", gold);
    printf("1. Health Potion - 50 Gold (+50 HP)\n");
    printf("2. Mana Potion - 80 Gold (+30 MP)\n");
    printf("3. Iron Sword - 500 Gold (+20 ATK)\n");
    printf("4. Leather Armor - 300 Gold (+15 DEF)\n");
    printf("5. Exit\n");

    // ให้ผู้เล่นเลือกไอเท็ม
    printf("Select item: ");
    scanf("%d", &item);

    // แสดงไอเทมที่ผู้เล่นเลือก
    printf("=== Purchase ===\n");
    switch (item)
    {
    case 1:
        price = 50;
        remaining_gold = gold - price;
        printf("Health Potion: 50 Gold\n");
        printf("Remaining : %d Gold\n", remaining_gold);
        printf("HP Bonus : +50 \n");
        break;
    case 2:
        price = 80;
        remaining_gold = gold - price;
        printf("Mana Potion: 80 Gold\n");
        printf("Remaining : %d Gold\n", remaining_gold);
        printf("MP Bonus : +30 \n");
        break;
    case 3:
        price = 500;
        remaining_gold = gold - price;
        printf("Iron Sword: 500 Gold\n");
        printf("Remaining : %d Gold\n", remaining_gold);
        printf("ATK Bonus : +20 \n");
        break;
    case 4:
        price = 300;
        remaining_gold = gold - price;
        printf("Leather Armor: 300 Gold\n");
        printf("Remaining : %d Gold\n", remaining_gold);
        printf("DEF Bonus : +15 \n");
        break;
    case 5:
        printf("Exiting\n");

        return 0;
    default:
        printf("Invalid item number\n");
        return 1;
    }
    if (remaining_gold < 0)
    {
        printf("Not enough gold!\n");
    }
    else
    {
        printf("Item purchased successfully! ✓\n");
    }

    return 0;
}