#include "cell.h"

CellHash cell_hash(Cell cell) {
    CellHash retval = ((CellHash)cell.y) & 0x0000FFFF;
    retval |= ((CellHash)cell.x) << 16;
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
