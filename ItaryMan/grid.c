#include "grid.h"
#include <stdio.h>

void Grid_Initialize(Grid *grid)
{
    grid->numRows = 12;
    grid->numCols = 12;
    grid->cellSize = 100;

    for (int row = 0; row < grid->numRows; row++)
    {
        for (int col = 0; col < grid->numCols; col++)
        {
            grid->grid[row][col] = 0;
        }
    }
}

void Grid_Print(Grid *grid)
{
    for (int row = 0; row < grid->numRows; row++)
    {
        for (int col = 0; col < grid->numCols; col++)
        {
            printf("%d ", grid->grid[row][col]);
        }

        printf("\n");
    }
}