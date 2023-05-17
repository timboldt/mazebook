#include "maze.h"

#include <memory.h>
#include <stdbool.h>
#include <string.h>

#define INVALID_CELL_HASH 0xDFDFDFDF
#define INVALID_EDGE_HASH 0xDFDFDFDFDFDFDFDF

void maze_init(Maze *maze, const char *name, int16_t width, int16_t height) {
    bool too_big = ((int)width * (int)height > MAX_CELLS);
    if (width < 1 || height < 1 ||
        too_big) {
        // Try to return something usable, but noticably wrong.
        width = 10;
        height = 10;
    }

    strncpy(maze->name, name, sizeof(maze->name));
    maze->name[sizeof(maze->name) - 1] = '\0';

    maze->width = width;
    maze->height = height;

    maze->entrance = (Cell){
        .x = width / 2,
        .y = height / 2,
    };
    maze->exit = (Cell){
        .x = width - 1,
        .y = 0,
    };

    memset(maze->cell_set, 0xDF, MAX_CELLS * sizeof(CellHash));
    for (int16_t x = 0; x < width; x++) {
        for (int16_t y = 0; y < height; y++) {
            Cell cell = {
                .x = x,
                .y = y,
            };
            maze_add_cell(maze, cell);
        }
    }

    memset(maze->edge_set, 0xDF, MAX_EDGES * sizeof(EdgeHash));
}

static size_t _find_cell(const Maze *maze, CellHash hash) {
    size_t bucket = hash % MAX_CELLS;
    for (;;) {
        if (maze->cell_set[bucket] == INVALID_CELL_HASH) {
            // Not found.
            break;
        }
        if (maze->cell_set[bucket] == hash) {
            // Found.
            break;
        }
        bucket = (bucket + 1) % MAX_CELLS;
    }
    return bucket;
}

void maze_add_cell(Maze *maze, Cell cell) {
    if (cell.x < 0 || cell.y < 0) {
        return;
    }
    if (cell.x >= maze->width || cell.y >= maze->height) {
        return;
    }
    CellHash hash = cell_hash(cell);
    maze->cell_set[_find_cell(maze, hash)] = hash;
}

bool maze_has_cell(const Maze *maze, Cell cell) {
    CellHash hash = cell_hash(cell);
    return maze->cell_set[_find_cell(maze, hash)] == hash;
}

bool maze_cell_has_connections(const Maze *maze, Cell cell) {
    if (maze_has_edge(maze, cell, north_of(cell))) {
        return true;
    }
    if (maze_has_edge(maze, cell, east_of(cell))) {
        return true;
    }
    if (maze_has_edge(maze, cell, south_of(cell))) {
        return true;
    }
    if (maze_has_edge(maze, cell, west_of(cell))) {
        return true;
    }

    return false;
}

static size_t _find_edge(const Maze *maze, EdgeHash hash) {
    size_t bucket = hash % MAX_EDGES;
    for (;;) {
        if (maze->edge_set[bucket] == INVALID_EDGE_HASH) {
            // Not found.
            break;
        }
        if (maze->edge_set[bucket] == hash) {
            // Found.
            break;
        }
        bucket = (bucket + 1) % MAX_EDGES;
    }
    return bucket;
}

void maze_add_edge(Maze *maze, Cell cell1, Cell cell2) {
    Edge edge = {
        .src_cell_hash = cell_hash(cell1),
        .dst_cell_hash = cell_hash(cell2),
    };
    EdgeHash hash = edge_hash(edge);
    maze->edge_set[_find_edge(maze, hash)] = hash;
}

bool maze_has_edge(const Maze *maze, Cell cell1, Cell cell2) {
    EdgeHash hash = edge_hash(new_edge(cell1, cell2));
    return maze->edge_set[_find_edge(maze, hash)] == hash;
}

/*
void maze_print_console(Maze *maze) {
    fmt.Print("+")
    for c := 0; c < m.cols; c++ {
        fmt.Print("---+")
    }
    fmt.Println()

    for r := 0; r < m.rows; r++ {
        middle := "|"
        bottom := "+"
        for c := 0; c < m.cols; c++ {
            thisCell := Cell(r, c)

            // Contents of cell.
            if thisCell.Hash() == m.start.Hash() {
                middle += " S "
            } else if thisCell.Hash() == m.end.Hash() {
                middle += " E "
            } else {
                middle += "   "
            }
            // Right wall of cell.
            if m.IsConnected(thisCell, thisCell.East()) {
                middle += " "
            } else {
                middle += "|"
            }
            // Bottom wall of cell.
            if m.IsConnected(thisCell, thisCell.South()) {
                bottom += "   "
            } else {
                bottom += "---"
            }
            bottom += "+"
        }
        fmt.Println(middle)
        fmt.Println(bottom)
    }
}

void maze_save_png(Maze *maze, const char *filename) {
    const cellSize = 20

    font, err := truetype.Parse(goregular.TTF)
    if err != nil {
        log.Fatal(err)
    }

    dc := gg.NewContext(m.cols*cellSize, m.rows*cellSize)

    // Set background.
    dc.SetRGBA(1, 1, 1, 1)
    dc.DrawRectangle(0, 0, float64(dc.Width()), float64(dc.Height()))
    dc.Fill()

    // Watermark with maze algorithm.
    dc.SetFontFace(truetype.NewFace(font, &truetype.Options{Size: 80}))
    dc.SetRGBA(0, 0, 0, 0.1)
    dc.DrawStringAnchored(m.name, float64(dc.Width())/2, float64(dc.Height())/2,
0.5, 0.5)

    // Set up line format.
    dc.SetRGBA(0, 0, 0, 1)
    dc.SetLineCap(gg.LineCapRound)
    dc.SetLineWidth(5)

    // Top border.
    dc.DrawLine(0, 0, float64(dc.Width()), 0)
    dc.Stroke()

    // Left border.
    dc.DrawLine(0, 0, 0, float64(dc.Height()))
    dc.Stroke()

    for r := 0; r < m.rows; r++ {
        for c := 0; c < m.cols; c++ {
            cellLeft := float64(c * cellSize)
            cellTop := float64(r * cellSize)
            thisCell := Cell(r, c)

            // Draw start and end symbols.
            if r == m.start.row && c == m.start.col {
                dc.SetRGBA(0, 0.5, 0, 0.5)
                dc.DrawCircle(cellLeft+0.5*cellSize, cellTop+0.5*cellSize,
cellSize*0.35) dc.Fill() dc.SetRGBA(0, 0, 0, 1)
                dc.SetFontFace(truetype.NewFace(font, &truetype.Options{Size:
6})) dc.DrawStringAnchored("Start", cellLeft+0.5*cellSize, cellTop+0.5*cellSize,
0.5, 0.5) } else if r == m.end.row && c == m.end.col { dc.SetRGBA(0.5, 0, 0.5,
0.5) dc.DrawCircle(cellLeft+0.5*cellSize, cellTop+0.5*cellSize, cellSize*0.35)
                dc.Fill()
                dc.SetRGBA(0, 0, 0, 1)
                dc.SetFontFace(truetype.NewFace(font, &truetype.Options{Size:
6})) dc.DrawStringAnchored("End", cellLeft+0.5*cellSize, cellTop+0.5*cellSize,
0.5, 0.5)
            }

            // Restore line color and draw right and bottom sides of cell, as
required. dc.SetRGBA(0, 0, 0, 1) if !m.IsConnected(thisCell, thisCell.East()) {
                dc.DrawLine(float64((c+1)*cellSize), float64(r*cellSize)+1,
float64((c+1)*cellSize), float64((r+1)*cellSize)-1) dc.Stroke()
            }
            if !m.IsConnected(thisCell, thisCell.South()) {
                dc.DrawLine(float64(c*cellSize)+1, float64((r+1)*cellSize),
float64((c+1)*cellSize)-1, float64((r+1)*cellSize)) dc.Stroke()
            }
        }
    }

    return dc.Image()
}

// NOTE: This is horribly inefficient. Consider redoing it as a full walk
// of the maze rather than recomputing the full path for each cell.
func (m *Maze) FindBestExitPoint() {
    path, _ := graph.ShortestPath(m.g, m.start.Hash(), m.end.Hash())
    best := len(path)
    for r := 0; r < m.rows; r++ {
        for c := 0; c < m.cols; c++ {
            thisCell := Cell(r, c)
            path, _ = graph.ShortestPath(m.g, thisCell.Hash(), m.end.Hash())
            newLen := len(path)
            if newLen > best {
                m.start = thisCell
                best = newLen
            }
        }
    }
}
*/
