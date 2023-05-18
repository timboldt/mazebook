#include <stdio.h>

#include "algo/binary_tree.h"
#include "maze.h"
#include "tigr.h"

int main(int argc, char **argv) {
    Maze mz;
    maze_init(&mz, "Test", 50, 30);

    printf("Maze:\n");
    printf("  Name:      %s\n", mz.name);
    printf("  Width:     %d\n", mz.width);
    printf("  Height:    %d\n", mz.height);

    printf("  Entrance:  (%d, %d)\n", mz.entrance.x, mz.entrance.y);
    printf("  Exit:      (%d, %d)\n", mz.exit.x, mz.exit.y);

    printf("  HasCell (42, 10): %d\n",
           maze_has_cell(&mz, (Cell){.x = 42, .y = 10}));

    apply_binary_tree(&mz);
    
    printf(
        "  HasEdge (42, 10)<->(42, 11): %d\n",
        maze_has_edge(&mz, (Cell){.x = 42, .y = 10}, (Cell){.x = 42, .y = 11}));

    maze_print_console(&mz);
}