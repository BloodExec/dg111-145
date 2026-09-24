#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SAVE_FILE_PATH "save.bin"

typedef struct
{
    float x, y;
    int hp, max_hp, level, score;
} GameData;

// ส่วนที่ 2 — saveGame
// เขียนข้อมูลเกมลงไฟล์
// คืนค่า 1 ถ้าสำเร็จ, 0 ถ้าเปิดไฟล์ไม่ได้
int saveGame(const char *path, const GameData *d)
{
    FILE *f = fopen(path, "wb"); // "wb" = write binary
    if (!f)
        return 0;
    fwrite(d, sizeof(GameData), 1, f); // เขียน struct ทั้งก้อนลงไฟล์
    fclose(f);
    return 1;
}

// ส่วนที่ 3 — loadGame
// คืนค่า 1 = สำเร็จ
// คืนค่า 0 = ไม่พบไฟล์
// คืนค่า -1 = ไฟล์เสีย
int loadGame(const char *path, GameData *d)
{
    FILE *f = fopen(path, "rb"); // "rb" = read binary
    if (!f)
        return 0;
    GameData tmp;
    size_t n = fread(&tmp, sizeof(GameData), 1, f); // อ่านกลับมาทั้งก้อน
    fclose(f);
    if (n != 1)
        return -1; // อ่านได้ไม่ครบ = ไฟล์เสีย
    *d = tmp;
    return 1;
}

// ส่วนที่ 4 — printData
// แสดงข้อมูลทั้งหมดในบรรทัดเดียว
void printData(const GameData *d)
{
    printf(
        "POS:%.1f,%.1f HP:%d/%d LEVEL:%d SCORE:%d\n",
        d->x,
        d->y,
        d->hp,
        d->max_hp,
        d->level,
        d->score);
}

// ส่วนที่ 5 — randomAction
// สุ่ม Action 1 ใน 5 แบบ
void randomAction(GameData *d)
{

    switch (rand() % 5)
    {

    // Move
    case 0:
    {
        int dx = rand() % 41 - 20;
        int dy = rand() % 41 - 20;

        d->x += dx;
        d->y += dy;

        printf(
            "[Move] You walked (%+d,%+d)\n",
            dx,
            dy);

        break;
    }

    // Fight
    case 1:
    {
        int dmg = 5 + rand() % 21;
        int gain = 50 + rand() % 101;

        d->hp -= dmg;
        d->score += gain;

        printf(
            "[Fight] Defeated a monster! -%d HP, +%d score\n",
            dmg,
            gain);

        break;
    }

    // Potion
    case 2:
    {
        int heal = 10 + rand() % 21;

        d->hp += heal;

        if (d->hp > d->max_hp)
        {
            d->hp = d->max_hp;
        }

        printf(
            "[Potion] Found a potion, +%d HP\n",
            heal);

        break;
    }

    // Treasure
    case 3:
    {
        int gain = 100 + rand() % 201;

        d->score += gain;

        printf(
            "[Treasure] Found a chest, +%d score\n",
            gain);

        break;
    }

    // Trap
    default:
    {
        int dmg = 20 + rand() % 21;

        d->hp -= dmg;

        printf(
            "[Trap] Ouch! -%d HP\n",
            dmg);

        break;
    }
    }

    // ถ้า HP <= 0 ให้เกิดใหม่
    if (d->hp <= 0)
    {

        printf(
            "You died! Respawn at (100,100) with full HP, score halved\n");

        d->x = 100.0f;
        d->y = 100.0f;
        d->hp = d->max_hp;
        d->score /= 2;
    }

    // Level up ทุก ๆ 400 คะแนนต่อ Level
    // เช่น Lv.7 ต้องมี 2800 คะแนน
    while (d->score >= d->level * 400)
    {

        d->level++;
        d->max_hp += 10;
        d->hp = d->max_hp;

        printf(
            "LEVEL UP! Now Lv.%d (max HP %d)\n",
            d->level,
            d->max_hp);
    }
}

// ส่วนที่ 6 — main
int main()
{

    // สุ่มตัวเลขครั้งเดียวตอนเริ่มโปรแกรม
    srand((unsigned)time(NULL));

    // ข้อมูลเริ่มต้น
    GameData data = {
        234.5f,
        189.0f,
        85,
        100,
        7,
        2350};

    int choice;

    // Menu loop
    while (1)
    {

        printf(
            "\n1. Save, "
            "2. Load, "
            "3. Random action, "
            "4. Show state, "
            "5. Quit: ");

        // รับเมนู
        if (scanf("%d", &choice) != 1)
        {

            // กรณีผู้ใช้กรอกตัวอักษร
            int c;

            while ((c = getchar()) != '\n' && c != EOF)
            {
            }

            if (c == EOF)
            {
                break;
            }

            continue;
        }

        // 1. Save
        if (choice == 1)
        {

            if (saveGame(SAVE_FILE_PATH, &data))
            {

                printf(
                    "Saved to %s\n",
                    SAVE_FILE_PATH);
            }
            else
            {

                printf(
                    "Cannot open %s for writing\n",
                    SAVE_FILE_PATH);
            }
        }

        // 2. Load
        else if (choice == 2)
        {

            printf("Before load: ");
            printData(&data);

            int result = loadGame(
                SAVE_FILE_PATH,
                &data);

            if (result == 1)
            {

                printf("Loaded! ");
                printData(&data);
            }
            else if (result == 0)
            {

                printf(
                    "No save file found (%s)\n",
                    SAVE_FILE_PATH);
            }
            else
            {

                printf(
                    "Save file %s is corrupted\n",
                    SAVE_FILE_PATH);
            }
        }

        // 3. Random action
        else if (choice == 3)
        {

            randomAction(&data);

            printf("Now: ");
            printData(&data);
        }

        // 4. Show state
        else if (choice == 4)
        {

            printData(&data);
        }

        // 5. Quit
        else if (choice == 5)
        {

            break;
        }
    }

    return 0;
}