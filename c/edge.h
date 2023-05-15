#pragma once

#include <stdint.h>

#include "cell.h"

// An Edge represents a bi-directional connection between two Cells in a Maze.
typedef struct {
    CellHash src_cell_hash;
    CellHash dst_cell_hash;
} Edge;

typedef uint64_t EdgeHash;

// Constructs a new Edge from two Cells.
Edge new_edge(Cell cell1, Cell cell2);

// Returns a hash of the Edge.
EdgeHash edge_hash(Edge edge);
