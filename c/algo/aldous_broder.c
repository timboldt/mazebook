#include "aldous_broder.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

void apply_aldous_broder(Maze *maze) {
    srand(time(NULL));
    strcpy(maze->name, "Aldous-Broder");

    Cell c = {
        .x = rand() % maze->width,
        .y = rand() % maze->height,
    };
    int unvisited = (int)maze->width * (int)maze->height - 1;
    while (unvisited > 0) {
        Cell next;
        int rnd = rand() % 4;
        switch (rnd) {
            case 0:
                next = north_of(c);
                break;
            case 1:
                next = east_of(c);
                break;
            case 2:
                next = south_of(c);
                break;
            case 3:
                next = west_of(c);
                break;
        }
        if (maze_has_cell(maze, next)) {
            if (!maze_cell_has_connections(maze, next)) {
                maze_add_edge(maze, c, next);
                unvisited--;
            }
            c = next;
        }
    }
}
