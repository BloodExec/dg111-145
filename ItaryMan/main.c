
#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

#define ITEM_COUNT 9
#define ITEMS_PER_TYPE 3
#define MAX_HEALTH 3
#define INVINCIBLE_TIME 3.0f

typedef struct
{
    int row, col, facing;
    Texture2D texture;
} Player;

typedef struct
{
    int row, col;
    float moveTimer;
    Texture2D north, south, east, west, texture;
} Monster;

typedef struct
{
    int row, col, type;
    bool active;
} Item;

typedef enum
{
    PLAYING,
    WON,
    GAME_OVER
} GameState;

// Check whether a monster occupies a cell
bool IsMonsterAt(int row, int col, Monster *a, Monster *b)
{
    return (row == a->row && col == a->col) ||
           (row == b->row && col == b->col);
}

// Draw a texture in a grid cell
void DrawCellTexture(Texture2D texture, int row, int col,
                     float offsetX, float offsetY, float cellSize)
{
    DrawTexturePro(
        texture,
        (Rectangle){0, 0, (float)texture.width,
                    (float)texture.height},
        (Rectangle){
            offsetX + col * cellSize,
            offsetY + row * cellSize,
            cellSize, cellSize},
        (Vector2){0, 0},
        0.0f,
        WHITE);
}

// Spawn items without overlapping walls, blocks, player,
// monsters, or other items
bool SpawnItem(Item *item, Item items[], Grid *grid,
               Player *player, Monster *tomato, Monster *cheese)
{
    for (int attempt = 0; attempt < 1000; attempt++)
    {
        int row = GetRandomValue(0, grid->numRows - 1);
        int col = GetRandomValue(0, grid->numCols - 1);

        if (grid->grid[row][col] != EMPTY)
            continue;

        if (row == player->row && col == player->col)
            continue;

        if (IsMonsterAt(row, col, tomato, cheese))
            continue;

        bool occupied = false;

        for (int i = 0; i < ITEM_COUNT; i++)
        {
            if (&items[i] == item || !items[i].active)
                continue;

            if (items[i].row == row && items[i].col == col)
            {
                occupied = true;
                break;
            }
        }

        if (occupied)
            continue;

        item->row = row;
        item->col = col;
        item->active = true;
        return true;
    }

    item->active = false;
    return false;
}

// Move a monster one random step
void UpdateMonster(Monster *monster, Grid *grid,
                   Monster *other, float deltaTime)
{
    monster->moveTimer -= deltaTime;

    if (monster->moveTimer > 0.0f)
        return;

    int direction = GetRandomValue(0, 3);
    int nextRow = monster->row;
    int nextCol = monster->col;

    switch (direction)
    {
    case NORTH:
        nextRow--;
        monster->texture = monster->north;
        break;

    case SOUTH:
        nextRow++;
        monster->texture = monster->south;
        break;

    case EAST:
        nextCol++;
        monster->texture = monster->east;
        break;

    case WEST:
        nextCol--;
        monster->texture = monster->west;
        break;
    }

    if (nextRow >= 0 && nextRow < grid->numRows &&
        nextCol >= 0 && nextCol < grid->numCols &&
        grid->grid[nextRow][nextCol] == EMPTY &&
        !(nextRow == other->row && nextCol == other->col))
    {
        monster->row = nextRow;
        monster->col = nextCol;
    }

    monster->moveTimer = 0.7f;
}

// Set up a new game
void ResetGame(Grid *grid, Player *player,
               Monster *tomato, Monster *cheese, Item items[],
               int *health, int *collected,
               float *invincible, GameState *state)
{
    Grid_Initialize(grid);

    // Fixed walls. The center has been cleared
    // so the player can move freely from the starting cell.

    // Upper and lower wall sections
    for (int col = 2; col <= 4; col++)
    {
        grid->grid[2][col] = OBSTACLE;
        grid->grid[9][col] = OBSTACLE;
    }

    for (int col = 7; col <= 9; col++)
    {
        grid->grid[2][col] = OBSTACLE;
        grid->grid[9][col] = OBSTACLE;
    }

    // Side wall sections
    for (int row = 4; row <= 7; row++)
    {
        grid->grid[row][2] = OBSTACLE;
        grid->grid[row][9] = OBSTACLE;
    }

    // No inner walls: these were removed to open the center.

    player->row = 5;
    player->col = 5;
    player->facing = SOUTH;

    tomato->row = 1;
    tomato->col = 1;
    tomato->moveTimer = 1.0f;

    cheese->row = 10;
    cheese->col = 10;
    cheese->moveTimer = 1.5f;

    for (int i = 0; i < ITEM_COUNT; i++)
    {
        items[i].type = i / ITEMS_PER_TYPE;
        items[i].active = false;
    }

    *health = MAX_HEALTH;
    *collected = 0;
    *invincible = 0.0f;
    *state = PLAYING;

    for (int i = 0; i < ITEM_COUNT; i++)
    {
        if (!SpawnItem(&items[i], items, grid,
                       player, tomato, cheese))
        {
            TraceLog(LOG_WARNING, "Could not place item %d", i);
        }
    }
}

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 800;
    const int hudHeight = 64;

    InitWindow(screenWidth, screenHeight, "ItaryMan");
    SetTargetFPS(60);
    SetRandomSeed((unsigned int)time(NULL));

    Grid grid;

    // Player images
    Texture2D playerNorth = LoadTexture("assets/player/north.png");
    Texture2D playerSouth = LoadTexture("assets/player/south.png");
    Texture2D playerEast = LoadTexture("assets/player/east.png");
    Texture2D playerWest = LoadTexture("assets/player/west.png");

    // Background and blocks
    Texture2D background = LoadTexture("assets/background.png");
    Texture2D blockTexture = LoadTexture("assets/block.jpg");
    Texture2D soilTexture = LoadTexture("assets/soil.png");

    // Collectible item images
    Texture2D itemTextures[3] = {
        LoadTexture("assets/item/cheese.png"),
        LoadTexture("assets/item/sauce.png"),
        LoadTexture("assets/item/leaf.png")};

    // Tomato monster
    Monster tomato = {0};
    tomato.north = LoadTexture("assets/tomato/north.png");
    tomato.south = LoadTexture("assets/tomato/south.png");
    tomato.east = LoadTexture("assets/tomato/east.png");
    tomato.west = LoadTexture("assets/tomato/west.png");
    tomato.texture = tomato.south;

    // Cheese monster
    Monster cheese = {0};
    cheese.north = LoadTexture("assets/cheese/north.png");
    cheese.south = LoadTexture("assets/cheese/south.png");
    cheese.east = LoadTexture("assets/cheese/east.png");
    cheese.west = LoadTexture("assets/cheese/west.png");
    cheese.texture = cheese.south;

    Player player = {5, 5, SOUTH, playerSouth};
    Item items[ITEM_COUNT] = {0};

    int health = MAX_HEALTH;
    int collectedItems = 0;
    float invincibleTimer = 0.0f;
    GameState gameState = PLAYING;

    ResetGame(&grid, &player, &tomato, &cheese, items,
              &health, &collectedItems,
              &invincibleTimer, &gameState);

    float availableHeight = (float)(screenHeight - hudHeight);
    float scaleX = (float)screenWidth /
                   (grid.numCols * grid.cellSize);
    float scaleY = availableHeight /
                   (grid.numRows * grid.cellSize);
    float scale = scaleX < scaleY ? scaleX : scaleY;
    float cellSize = grid.cellSize * scale;

    float offsetX = (screenWidth - grid.numCols * cellSize) / 2.0f;
    float offsetY = hudHeight +
                    (availableHeight - grid.numRows * cellSize) / 2.0f;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (gameState != PLAYING && IsKeyPressed(KEY_R))
        {
            ResetGame(&grid, &player, &tomato, &cheese, items,
                      &health, &collectedItems,
                      &invincibleTimer, &gameState);

            player.texture = playerSouth;
            tomato.texture = tomato.south;
            cheese.texture = cheese.south;
        }

        if (gameState == PLAYING)
        {
            if (invincibleTimer > 0.0f)
            {
                invincibleTimer -= dt;
                if (invincibleTimer < 0.0f)
                    invincibleTimer = 0.0f;
            }

            // Player movement
            int nr = player.row;
            int nc = player.col;
            bool moving = false;

            if (IsKeyPressed(KEY_W))
            {
                nr--;
                player.facing = NORTH;
                player.texture = playerNorth;
                moving = true;
            }
            else if (IsKeyPressed(KEY_S))
            {
                nr++;
                player.facing = SOUTH;
                player.texture = playerSouth;
                moving = true;
            }
            else if (IsKeyPressed(KEY_D))
            {
                nc++;
                player.facing = EAST;
                player.texture = playerEast;
                moving = true;
            }
            else if (IsKeyPressed(KEY_A))
            {
                nc--;
                player.facing = WEST;
                player.texture = playerWest;
                moving = true;
            }

            if (moving &&
                nr >= 0 && nr < grid.numRows &&
                nc >= 0 && nc < grid.numCols &&
                grid.grid[nr][nc] == EMPTY)
            {
                player.row = nr;
                player.col = nc;
            }

            // Space: build or destroy player blocks
            if (IsKeyPressed(KEY_SPACE))
            {
                int dr = 0, dc = 0;

                switch (player.facing)
                {
                case NORTH:
                    dr = -1;
                    break;
                case SOUTH:
                    dr = 1;
                    break;
                case EAST:
                    dc = 1;
                    break;
                case WEST:
                    dc = -1;
                    break;
                }

                int r = player.row + dr;
                int c = player.col + dc;

                if (r >= 0 && r < grid.numRows &&
                    c >= 0 && c < grid.numCols)
                {
                    if (grid.grid[r][c] == ICE_BLOCK)
                    {
                        grid.grid[r][c] = EMPTY;
                    }
                    else if (grid.grid[r][c] == EMPTY)
                    {
                        while (r >= 0 && r < grid.numRows &&
                               c >= 0 && c < grid.numCols)
                        {
                            if (grid.grid[r][c] != EMPTY ||
                                IsMonsterAt(r, c, &tomato, &cheese))
                                break;

                            grid.grid[r][c] = ICE_BLOCK;
                            r += dr;
                            c += dc;
                        }
                    }
                }
            }

            // Monsters move randomly
            UpdateMonster(&tomato, &grid, &cheese, dt);
            UpdateMonster(&cheese, &grid, &tomato, dt);

            // Collision damage
            if (invincibleTimer <= 0.0f &&
                IsMonsterAt(player.row, player.col, &tomato, &cheese))
            {
                health--;
                invincibleTimer = INVINCIBLE_TIME;

                if (health <= 0)
                {
                    health = 0;
                    gameState = GAME_OVER;
                }
            }

            // Pick up items
            if (gameState == PLAYING)
            {
                for (int i = 0; i < ITEM_COUNT; i++)
                {
                    if (items[i].active &&
                        items[i].row == player.row &&
                        items[i].col == player.col)
                    {
                        items[i].active = false;
                        collectedItems++;
                    }
                }

                if (collectedItems == ITEM_COUNT)
                    gameState = WON;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        // HUD
        DrawRectangle(0, 0, screenWidth, hudHeight,
                      (Color){20, 24, 34, 255});

        DrawText("ITARYMAN", 16, 8, 20, RAYWHITE);
        DrawText("HEALTH", 16, 36, 16, LIGHTGRAY);

        for (int i = 0; i < MAX_HEALTH; i++)
        {
            DrawCircle(100 + i * 24, 44, 8,
                       i < health ? RED : DARKGRAY);
        }

        DrawText(TextFormat("ITEMS: %d / 9", collectedItems),
                 500, 24, 22, GOLD);

        // Background image
        DrawTexturePro(
            background,
            (Rectangle){0, 0, (float)background.width,
                        (float)background.height},
            (Rectangle){offsetX, offsetY,
                        grid.numCols * cellSize,
                        grid.numRows * cellSize},
            (Vector2){0, 0}, 0.0f, WHITE);

        // Permanent walls and player-created blocks
        for (int r = 0; r < grid.numRows; r++)
        {
            for (int c = 0; c < grid.numCols; c++)
            {
                if (grid.grid[r][c] == OBSTACLE)
                    DrawCellTexture(blockTexture, r, c,
                                    offsetX, offsetY, cellSize);
                else if (grid.grid[r][c] == ICE_BLOCK)
                    DrawCellTexture(soilTexture, r, c,
                                    offsetX, offsetY, cellSize);
            }
        }

        // Items
        for (int i = 0; i < ITEM_COUNT; i++)
        {
            if (items[i].active)
            {
                DrawCellTexture(itemTextures[items[i].type],
                                items[i].row, items[i].col,
                                offsetX, offsetY, cellSize);
            }
        }

        // Monsters
        DrawCellTexture(tomato.texture, tomato.row, tomato.col,
                        offsetX, offsetY, cellSize);
        DrawCellTexture(cheese.texture, cheese.row, cheese.col,
                        offsetX, offsetY, cellSize);

        // Player flashes during the 3-second invincibility period
        if (invincibleTimer <= 0.0f ||
            ((int)(invincibleTimer * 10) % 2 == 0))
        {
            DrawCellTexture(player.texture, player.row, player.col,
                            offsetX, offsetY, cellSize);
        }

        // Win / Game Over screen
        if (gameState != PLAYING)
        {
            DrawRectangle(0, 0, screenWidth, screenHeight,
                          (Color){0, 0, 0, 190});

            const char *message =
                gameState == WON ? "YOU WIN!" : "GAME OVER";

            const char *subtitle =
                gameState == WON
                    ? "You collected all 9 items!"
                    : "You ran out of health!";

            DrawText(message,
                     (screenWidth - MeasureText(message, 52)) / 2,
                     320, 52, gameState == WON ? GOLD : RED);

            DrawText(subtitle,
                     (screenWidth - MeasureText(subtitle, 20)) / 2,
                     390, 20, RAYWHITE);

            DrawText("Press R to restart",
                     (screenWidth - MeasureText("Press R to restart", 20)) / 2,
                     440, 20, LIGHTGRAY);
        }

        EndDrawing();
    }

    // Release textures
    UnloadTexture(playerNorth);
    UnloadTexture(playerSouth);
    UnloadTexture(playerEast);
    UnloadTexture(playerWest);

    UnloadTexture(background);
    UnloadTexture(blockTexture);
    UnloadTexture(soilTexture);

    for (int i = 0; i < 3; i++)
        UnloadTexture(itemTextures[i]);

    UnloadTexture(tomato.north);
    UnloadTexture(tomato.south);
    UnloadTexture(tomato.east);
    UnloadTexture(tomato.west);

    UnloadTexture(cheese.north);
    UnloadTexture(cheese.south);
    UnloadTexture(cheese.east);
    UnloadTexture(cheese.west);

    CloseWindow();
    return 0;
}
