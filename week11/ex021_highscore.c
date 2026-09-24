#include <stdio.h>
#include <string.h>

#define MAX_ENTRIES 5
#define NAME_LEN 30
#define FILE_NAME "highscores.txt"

typedef struct
{
    char name[NAME_LEN];
    int score;
} Entry;

// ส่วนที่ 2 — createDefault
// เขียนคะแนนเริ่มต้นลงไฟล์
void createDefault(const char *filename)
{
    FILE *f = fopen(filename, "w");

    if (f == NULL)
    {
        printf("Cannot create %s\n", filename);
        return;
    }

    fprintf(f, "Diana 15600\n");
    fprintf(f, "Bob 12300\n");
    fprintf(f, "Eve 9800\n");
    fprintf(f, "Alice 8500\n");
    fprintf(f, "Charlie 7200\n");

    fclose(f);
}

// ส่วนที่ 3 — loadScores
// อ่านข้อมูลจากไฟล์
int loadScores(const char *filename, Entry list[])
{
    FILE *f = fopen(filename, "r");

    if (f == NULL)
    {
        return 0;
    }

    int count = 0;
    Entry e;

    while (
        count < MAX_ENTRIES &&
        fscanf(f, "%29s %d", e.name, &e.score) == 2)
    {
        list[count] = e;
        count++;
    }

    fclose(f);

    return count;
}

// ส่วนที่ 3 — saveScores
// บันทึกข้อมูลลงไฟล์
void saveScores(
    const char *filename,
    const Entry list[],
    int count)
{
    FILE *f = fopen(filename, "w");

    if (f == NULL)
    {
        printf("Cannot write %s\n", filename);
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(
            f,
            "%s %d\n",
            list[i].name,
            list[i].score);
    }

    fclose(f);
}

// ส่วนที่ 4 — showLeaderboard
// แสดงตารางคะแนน
void showLeaderboard(
    const Entry list[],
    int count)
{
    printf("=== High Scores ===\n");

    for (int i = 0; i < count; i++)
    {
        printf(
            "%d. %-12s %6d\n",
            i + 1,
            list[i].name,
            list[i].score);
    }

    printf("===================\n");
}

// ส่วนที่ 5 — addScore
// เพิ่มคะแนนโดยเรียงจากมากไปน้อย
int addScore(
    Entry list[],
    int *count,
    const char *name,
    int score)
{
    int pos = *count;

    // หาตำแหน่งที่จะใส่คะแนนใหม่
    for (int i = 0; i < *count; i++)
    {
        if (score > list[i].score)
        {
            pos = i;
            break;
        }
    }

    // ถ้าอยู่นอก Top 5
    if (pos >= MAX_ENTRIES)
    {
        return 0;
    }

    // เลื่อนข้อมูลด้านหลังลง 1 ช่อง
    int last = (*count < MAX_ENTRIES)
                   ? *count
                   : MAX_ENTRIES - 1;

    for (int i = last; i > pos; i--)
    {
        list[i] = list[i - 1];
    }

    // ใส่ข้อมูลใหม่
    strncpy(
        list[pos].name,
        name,
        NAME_LEN - 1);

    list[pos].name[NAME_LEN - 1] = '\0';
    list[pos].score = score;

    // เพิ่มจำนวนข้อมูล ถ้ายังไม่ครบ 5 คน
    if (*count < MAX_ENTRIES)
    {
        (*count)++;
    }

    return 1;
}

// ส่วนที่ 6 — main
int main()
{

    Entry list[MAX_ENTRIES];

    // 1. โหลดข้อมูลจากไฟล์
    // ถ้าไม่มีไฟล์ ให้สร้างข้อมูลเริ่มต้น
    int count = loadScores(FILE_NAME, list);

    if (count == 0)
    {
        printf(
            "%s not found. Creating default file...\n",
            FILE_NAME);

        createDefault(FILE_NAME);

        count = loadScores(FILE_NAME, list);
    }

    // 2. แสดง Leaderboard ปัจจุบัน
    showLeaderboard(list, count);

    // 3. รับคะแนนใหม่จนกว่าจะพิมพ์ q
    char name[NAME_LEN];
    int score;

    while (1)
    {

        printf("Enter name (q to quit): ");

        if (
            scanf("%29s", name) != 1 ||
            strcmp(name, "q") == 0)
        {
            break;
        }

        printf("Enter score: ");

        if (scanf("%d", &score) != 1)
        {

            // ถ้ากรอกคะแนนไม่ถูกต้อง
            // ล้างข้อมูลที่ค้างอยู่ใน buffer
            int c;

            while ((c = getchar()) != '\n' && c != EOF)
            {
            }

            printf("Invalid score\n");

            continue;
        }

        // 4. เพิ่มคะแนนถ้าเข้า Top 5
        if (
            addScore(
                list,
                &count,
                name,
                score))
        {

            printf(
                "Congratulations! You made the top %d!\n",
                MAX_ENTRIES);

            saveScores(
                FILE_NAME,
                list,
                count);
        }
        else
        {

            printf(
                "Score too low for the top %d.\n",
                MAX_ENTRIES);
        }

        // แสดง Leaderboard หลังเพิ่มคะแนน
        showLeaderboard(list, count);
    }

    printf("Goodbye!\n");

    return 0;
}