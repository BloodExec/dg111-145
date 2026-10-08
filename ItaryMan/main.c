#include <raylib.h>
#include "Grid.h"

// =====================================================
// Player
// =====================================================

typedef struct
{
    int row;
    int col;
    Texture2D texture;

} Player;

// =====================================================
// Main
// =====================================================

int main()
{
    // =================================================
    // Window
    // =================================================

    InitWindow(800, 800, "Italy Man");
    SetTargetFPS(60);

    // =================================================
    // Grid
    // =================================================

    Grid grid;

    Grid_Initialize(&grid);

    // =================================================
    // Load Player Textures
    // =================================================

    Texture2D playerNorth =
        LoadTexture("assets/north.png");

    Texture2D playerSouth =
        LoadTexture("assets/south.png");

    Texture2D playerEast =
        LoadTexture("assets/east.png");

    Texture2D playerWest =
        LoadTexture("assets/west.png");

    // =================================================
    // Load Background
    // =================================================

    Texture2D background =
        LoadTexture("assets/background.jpg");

    // =================================================
    // Player
    // =================================================

    Player player;

    player.row = 5;
    player.col = 5;

    // เริ่มต้นหันลง
    player.texture = playerSouth;

    // =================================================
    // Map Size
    // =================================================

    int worldWidth =
        grid.numCols * grid.cellSize;

    int worldHeight =
        grid.numRows * grid.cellSize;

    // =================================================
    // Screen Size
    // =================================================

    int screenWidth = 800;
    int screenHeight = 800;

    // =================================================
    // Scale
    // =================================================

    float scaleX =
        (float)screenWidth / worldWidth;

    float scaleY =
        (float)screenHeight / worldHeight;

    // ใช้ scale ที่เล็กกว่าเพื่อให้ Map เห็นทั้งหมด
    float scale =
        (scaleX < scaleY) ? scaleX : scaleY;

    // =================================================
    // Display Cell Size
    // =================================================

    float displayCellSize =
        grid.cellSize * scale;

    // =================================================
    // Player Display Size
    // =================================================

    float playerSize =
        displayCellSize;

    // =================================================
    // Game Loop
    // =================================================

    while (!WindowShouldClose())
    {
        // =================================================
        // INPUT
        // =================================================

        bool up =
            IsKeyPressed(KEY_W);

        bool down =
            IsKeyPressed(KEY_S);

        bool left =
            IsKeyPressed(KEY_A);

        bool right =
            IsKeyPressed(KEY_D);

        // =================================================
        // 4 DIRECTIONS
        // =================================================

        // W = North
        if (up)
        {
            if (player.row > 0)
                player.row--;

            player.texture = playerNorth;
        }

        // S = South
        else if (down)
        {
            if (player.row < grid.numRows - 1)
                player.row++;

            player.texture = playerSouth;
        }

        // A = West
        else if (left)
        {
            if (player.col > 0)
                player.col--;

            player.texture = playerWest;
        }

        // D = East
        else if (right)
        {
            if (player.col < grid.numCols - 1)
                player.col++;

            player.texture = playerEast;
        }

        // =================================================
        // DRAW
        // =================================================

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // =================================================
        // BACKGROUND
        // =================================================

        DrawTexturePro(
            background,

            // Source
            (Rectangle){
                0,
                0,
                background.width,
                background.height},

            // Destination
            (Rectangle){
                0,
                0,
                screenWidth,
                screenHeight},

            // Origin
            (Vector2){
                0,
                0},

            // Rotation
            0.0f,

            WHITE);

        // =================================================
        // GRID LINES
        // =================================================

        Color gridColor =
            Fade(BLACK, 0.15f);

        // Vertical lines
        for (int col = 0;
             col <= grid.numCols;
             col++)
        {
            float x =
                col * displayCellSize;

            DrawLine(
                (int)x,
                0,
                (int)x,
                screenHeight,
                gridColor);
        }

        // Horizontal lines
        for (int row = 0;
             row <= grid.numRows;
             row++)
        {
            float y =
                row * displayCellSize;

            DrawLine(
                0,
                (int)y,
                screenWidth,
                (int)y,
                gridColor);
        }

        // =================================================
        // PLAYER POSITION
        // =================================================

        float playerX =
            player.col * displayCellSize;

        float playerY =
            player.row * displayCellSize;

        // =================================================
        // PLAYER
        // =================================================

        DrawTexturePro(
            player.texture,

            // Source
            (Rectangle){
                0,
                0,
                64,
                64},

            // Destination
            (Rectangle){
                playerX,
                playerY,
                playerSize,
                playerSize},

            // Origin
            (Vector2){
                0,
                0},

            // Rotation
            0.0f,

            WHITE);

        EndDrawing();
    }

    // =================================================
    // Unload Player Textures
    // =================================================

    UnloadTexture(playerNorth);
    UnloadTexture(playerSouth);
    UnloadTexture(playerEast);
    UnloadTexture(playerWest);

    // =================================================
    // Unload Background
    // =================================================

    UnloadTexture(background);

    // =================================================
    // Close Window
    // =================================================

    CloseWindow();

    return 0;
}