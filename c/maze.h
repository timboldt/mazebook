#pragma once

#include <stdbool.h>

#include "cell.h"
#include "edge.h"

#define MAX_CELLS 3989
#define MAX_EDGES 7993

typedef struct {
    char name[80];

    int16_t width;
    int16_t height;

    Cell entrance;
    Cell exit;

    CellHash cell_set[MAX_CELLS];
    EdgeHash edge_set[MAX_EDGES];
} Maze;

void maze_init(Maze *maze, const char *name, int16_t width, int16_t height);

void maze_add_cell(Maze *maze, Cell cell);
bool maze_has_cell(const Maze *maze, Cell cell);
bool maze_cell_has_connections(const Maze *maze, Cell cell);

void maze_add_edge(Maze *maze, Cell cell1, Cell cell2);
bool maze_has_edge(const Maze *maze, Cell cell1, Cell cell2);

void maze_print_console(const Maze *maze);
void maze_save_png(const Maze *maze, const char *filename);

void maze_update_entrance(Maze *maze);
