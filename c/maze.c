#include "maze.h"

#include <memory.h>
#include <string.h>

#define INVALID_CELL_HASH 0xDFDFDFDF
#define INVALID_EDGE_HASH 0xDFDFDFDFDFDFDFDF

void maze_init(Maze *maze, const char *name, int16_t width, int16_t height) {
    //!!!! ASSERTS on name length, width and height?

    strncpy(maze->name, name, sizeof(maze->name));
    maze->name[sizeof(maze->name)-1] = '\0';

    maze->width = width;
    maze->height = height;

    maze->entrance = (Cell){
        .x = 0,
        .y = height - 1,
    };
    maze->exit = (Cell){
        .x = width - 1,
        .y = 0,
    };

    memset(maze->cell_set, 0xDF, MAX_CELLS*sizeof(CellHash));
    memset(maze->edge_set, 0xDF, MAX_EDGES*sizeof(EdgeHash));
}