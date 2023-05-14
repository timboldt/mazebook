#include "cell.h"

int hash(Cell cell) {
    int retval = (int)cell.x * 1000 + cell.y;
    return retval;
}

Cell north_of(Cell cell) {
    Cell retval = {
        .x = cell.x,
        .y = cell.y + 1,
    };
    return retval;
}

Cell east_of(Cell cell) {
    Cell retval = {
        .x = cell.x + 1,
        .y = cell.y,
    };
    return retval;
}

Cell south_of(Cell cell) {
    Cell retval = {
        .x = cell.x,
        .y = cell.y - 1,
    };
    return retval;
}

Cell west_of(Cell cell) {
    Cell retval = {
        .x = cell.x - 1,
        .y = cell.y,
    };
    return retval;
}
