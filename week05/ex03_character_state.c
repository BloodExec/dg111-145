#include <stdio.h>
#include <math.h>
int main()
{
    int hp;
    int max_hp;
    int damage;
    _Bool is_poisoned;
    int attack_count;
    char *status;

    // รับค่าตัวแปรจากผู้ใช้
    printf("Max HP: ");
    scanf("%d", &max_hp);
    printf("Damage Taken: ");
    scanf("%d", &damage);
    // ถ้า hp น้อยกว่า 0 ให้ hp = 0
    hp = max_hp - damage;
    if (hp < 0)
        hp = 0;
    printf("Poisoned (0/1): ");
    scanf("%d", &is_poisoned);
    printf("Attack Count: ");
    scanf("%d", &attack_count);

    // เงื่อนไขต่างๆ
    if (hp <= 0)
    {
        status = "DEAD";
    }
    else if (hp <= max_hp * 25 / 100)
    {
        status = "CRITICAL";
    }
    else if (is_poisoned == 1)
    {
        status = "POISONED";
    }
    else if (attack_count > 0 && attack_count % 5 == 0)
    {
        status = "NORMAL + Ultimate!";
    }
    else
    {
        status = "NORMAL";
    }
    printf("=== Character Status ===\n");
    // แถบแสดง HP
    int filled = hp * 10 / max_hp;
    printf("HP : [");
    for (int i = 0; i < 10; i++)
    {
        printf(i < filled ? "█" : "-");
    }
    printf("] %d/%d\n", hp, max_hp);
    if (hp <= max_hp * 25 / 100)
    {
        printf(" (⚠️  CRITICAL!)\n");
    }
    printf("State: %s\n", status);
    if (attack_count > 0 && attack_count % 5 == 0)
    {
        printf("🌟  Ultimate Ready! (Attack #%d)\n", attack_count);
    }
    return 0;
}
