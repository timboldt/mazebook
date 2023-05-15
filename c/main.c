#include <stdio.h>

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

    printf("  cell_set[42]: %08x\n", mz.cell_set[42]);
    printf("  edge_set[42]: %016llx\n", mz.edge_set[42]);
}