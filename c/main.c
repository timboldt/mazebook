#include <stdio.h>

#include "algo/aldous_broder.h"
#include "algo/binary_tree.h"
#include "algo/sidewinder.h"
#include "maze.h"
#include "tigr.h"

int main(int argc, char **argv) {
    Maze mz;
    maze_init(&mz, "Test", 50, 30);


    apply_aldous_broder(&mz);
    maze_update_entrance(&mz);

    printf("Name:      %s\n", mz.name);
    printf("Width:     %d\n", mz.width);
    printf("Height:    %d\n", mz.height);
    maze_print_console(&mz);
}