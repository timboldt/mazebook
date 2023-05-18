#include "binary_tree.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

void apply_binary_tree(Maze *maze) {
    srand(time(NULL));
    strcpy(maze->name, "Binary Tree");
    for (int x = 0; x < maze->width; x++) {
        for (int y = 0; y < maze->height; y++) {
            Cell c = {.x = x, .y = y};
            Cell north = north_of(c);
            Cell east = east_of(c);

            // Pick between linking vertically or horizontally.
            int rnd = rand() % 2;

            if (!maze_has_cell(maze, north) && !maze_has_cell(maze, east)) {
                // Neither will work.
                rnd = -1;
            } else if (!maze_has_cell(maze, north)) {
                // Linking rows won't work, so use columns.
                rnd = 1;
            } else if (!maze_has_cell(maze, east)) {
                // Linking columns won't work, so use rows.
                rnd = 0;
            }

            if (rnd == 0) {
                // Link to next row.
                maze_add_edge(maze, c, north);
            } else if (rnd == 1) {
                // Link to next column.
                maze_add_edge(maze, c, east);
            }
        }
    }
}
