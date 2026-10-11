
#ifndef GRID_H
#define GRID_H

#define EMPTY 0
#define ICE_BLOCK 1
#define OBSTACLE 2

typedef struct
{
    int grid[12][12];
    int numRows;
    int numCols;
    int cellSize;
} Grid;

void Grid_Initialize(Grid *grid);
void Grid_Print(Grid *grid);

#endif
