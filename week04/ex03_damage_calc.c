#include <stdio.h>
#include <math.h>
int main()
{
    // ตัวแปล
    int player_attack;
    int enemy_defense;
    int hit_number;
    int damage;
    int crit;
    int crit_damage;
    int hp_enemy = 500;

    // รับค่าและแสดงผลลัพธ์
    printf("=== COMBAT SIMULATOR ===\n");
    printf("Player Attack :  ");
    scanf("%d", &player_attack);
    printf("Enemy Defense :  ");
    scanf("%d", &enemy_defense);
    printf("Hit Number :  ");
    scanf("%d", &hit_number);
    damage = player_attack - enemy_defense;
    crit = hit_number % 5;
    if (crit == 0)
    {
        crit_damage = (int)ceil((float)damage * 1.5f);
        printf("Damage : %d ** CRITICAL HIT! x1.5 ***\n", crit_damage);
        printf("Enemy HP : %d -> %d\n", hp_enemy, hp_enemy - crit_damage);
    }
    else
    {
        printf("Damage : %d (Normal)\n", damage);
        printf("Enemy HP : %d -> %d\n", hp_enemy, hp_enemy - damage);
    }

    return 0;
}