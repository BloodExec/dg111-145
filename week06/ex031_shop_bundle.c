#include <stdio.h>
#include <math.h>
int main()
{
    // หน้าต่างร้านค้า
    printf("=== ITEM SHOP ===\n");
    printf("Gold: 1,000\n");
    printf("\n");
    printf("1. Health Potion - 50 Gold (+50 HP)\n");
    printf("2. Mana Potion - 80 Gold (+30 MP)\n");
    printf("3. Iron Sword - 500 Gold (+20 ATK)\n");
    printf("4. Leather Armor - 300 Gold (+15 DEF)\n");
    printf("5. Checkout\n");

    // การซื้อไอเท็ม
    int gold = 1000;
    int selection;
    int total = 0;
    _Bool boughtSword = 0, boughtArmor = 0;
    do
    {
        printf("Select item: ");
        scanf("%d", &selection);
        switch (selection)
        {
        case 1:
            if (total + 50 > gold)
                printf("Not enough Gold!\n");
            else
            {
                printf("Health Potion added to cart.\n");
                total += 50;
            }
            break;
        case 2:
            if (total + 80 > gold)
                printf("Not enough Gold!\n");
            else
            {
                printf("Mana Potion added to cart.\n");
                total += 80;
            }
            break;
        case 3:
            if (total + 500 > gold)
                printf("Not enough Gold!\n");
            else
            {
                printf("Iron Sword added to cart.\n");
                total += 500;
                boughtSword = 1;
            }
            break;
        case 4:
            if (total + 300 > gold)
                printf("Not enough Gold!\n");
            else
            {
                printf("Leather Armor added to cart.\n");
                total += 300;
                boughtArmor = 1;
            }
            break;
        case 5:
            printf("=== Checkout ===\n");
        }
    } while (selection != 5);
    if (boughtSword && boughtArmor)
    {
        total = total * 90 / 100; // ลด 10%
        printf("Warrior Bundle! (-10%%)\n");
    }
    printf("Total Paid: %d Gold\n", total);
    printf("Remaining : %d Gold\n", gold - total);

    return 0;
}