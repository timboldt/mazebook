#pragma once

#include <stdint.h>

// A Cell represents a location in the Maze. It can also be thought of as a node
// in a graph.
typedef struct {
    int16_t x;
    int16_t y;
} Cell;

typedef uint32_t CellHash;

// Constructs a cell.
Cell new_cell(int x, int y);

// Returns a hash of the cell.
CellHash cell_hash(Cell cell);

// Returns the neighboring cell in the specified direction.
Cell north_of(Cell cell);
Cell east_of(Cell cell);
Cell south_of(Cell cell);
Cell west_of(Cell cell);