#include "sidewinder.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

void apply_sidewinder(Maze *maze) {
    srand(time(NULL));
    for (int y = 0; y < maze->height; y++) {
        strcpy(maze->name, "Sidewinder");
        size_t run_items = 0;
        Cell run[1024];
        for (int x = 0; x < maze->width; x++) {
            Cell c = {.x = x, .y = y};
            run[run_items++] = c;

            // Flip a coin to decide whether to end the run.
            int rnd = rand() % 2;

            bool should_close = !maze_has_cell(maze, east_of(c)) ||
                                (rnd == 0 && maze_has_cell(maze, north_of(c)));

            if (should_close) {
                // Pick a random entry from the run.
                Cell chosen = run[rand() % run_items];

                // Link to the next row from the random cell.
                maze_add_edge(maze, chosen, north_of(chosen));
                run_items = 0;
            } else {
                // Link to next column.
                maze_add_edge(maze, c, east_of(c));
            }
        }
    }
}
