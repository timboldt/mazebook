#pragma once

#include <stdint.h>

typedef struct {
    int16_t x;
    int16_t y;
} Cell;

// Returns a hash of the cell.
int hash(Cell cell);

// Returns the neighboring cell in the specified direction.
Cell north_of(Cell cell);
Cell east_of(Cell cell);
Cell south_of(Cell cell);
Cell west_of(Cell cell);