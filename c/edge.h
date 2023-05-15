#pragma once

#include <stdint.h>

#include "cell.h"

// An Edge represents a bi-directional connection between two Cells in a Maze.
typedef struct {
    uint32_t src_cell_hash;
    uint32_t dst_cell_hash;
} Edge;

// Constructs a new Edge from two Cells.
Edge new_edge(Cell cell1, Cell cell2);

// Returns a hash of the Edge.
uint64_t hash(Edge edge);
