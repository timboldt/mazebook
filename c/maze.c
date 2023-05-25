#include "maze.h"

#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define INVALID_CELL_HASH 0xDFDFDFDF
#define INVALID_EDGE_HASH 0xDFDFDFDFDFDFDFDF

void maze_init(Maze *maze, const char *name, int16_t width, int16_t height) {
    bool too_big = ((int)width * (int)height > MAX_CELLS);
    if (width < 1 || height < 1 || too_big) {
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
    EdgeHash hash = edge_hash(new_edge(cell1, cell2));
    maze->edge_set[_find_edge(maze, hash)] = hash;
}

bool maze_has_edge(const Maze *maze, Cell cell1, Cell cell2) {
    EdgeHash hash = edge_hash(new_edge(cell1, cell2));
    return maze->edge_set[_find_edge(maze, hash)] == hash;
}

void maze_print_console(const Maze *maze) {
    putchar('+');
    for (int x = 0; x < maze->width; x++) {
        printf("---+");
    }
    putchar('\n');

    for (int y = maze->height - 1; y >= 0; y--) {
        size_t idx = 0;
        char middle[300];
        char bottom[300];

        middle[idx] = '|';
        bottom[idx] = '+';
        idx++;

        for (int x = 0; x < maze->width; x++) {
            Cell cell = {.x = x, .y = y};

            if (idx >= sizeof(middle) - 6) {
                // Maze is too wide to display.
                middle[idx] = '?';
                bottom[idx] = '?';
                idx++;
                break;
            }

            // Contents of cell.
            middle[idx] = ' ';
            if (cell_hash(cell) == cell_hash(maze->entrance)) {
                middle[idx + 1] = 'S';
            } else if (cell_hash(cell) == cell_hash(maze->exit)) {
                middle[idx + 1] = 'E';
            } else {
                middle[idx + 1] = ' ';
            }
            middle[idx + 2] = ' ';
            // Right wall of cell.
            if (maze_has_edge(maze, cell, east_of(cell))) {
                middle[idx + 3] = ' ';
            } else {
                middle[idx + 3] = '|';
            }
            // Bottom wall of cell.
            if (maze_has_edge(maze, cell, south_of(cell))) {
                bottom[idx] = ' ';
                bottom[idx + 1] = ' ';
                bottom[idx + 2] = ' ';
            } else {
                bottom[idx] = '-';
                bottom[idx + 1] = '-';
                bottom[idx + 2] = '-';
            }
            bottom[idx + 3] = '+';
            idx += 4;
        }
        middle[idx] = '\0';
        bottom[idx] = '\0';
        printf("%s\n", middle);
        printf("%s\n", bottom);
    }
}

int _path_length(Maze *maze, Cell prev, Cell curr, Cell end) {
    if (cell_hash(curr) == cell_hash(end)) {
        return 0;
    }
    int best_path = 9999;
    for (int i = 0; i < 4; i++) {
        Cell next;
        switch (i) {
            case 0:
                next = north_of(curr);
                break;
            case 1:
                next = east_of(curr);
                break;
            case 2:
                next = south_of(curr);
                break;
            case 3:
                next = west_of(curr);
                break;
        }
        // If we are connected to the next cell and it is not the cell we came
        // from, consider it as a candidate.
        if (maze_has_edge(maze, curr, next) &&
            cell_hash(next) != cell_hash(prev)) {
            int plen = _path_length(maze, curr, next, end);
            if (plen < best_path) {
                best_path = plen;
            }
        }
    }
    return best_path + 1;
}

void maze_update_entrance(Maze *maze) {
    int longest = 0;
    for (int y1 = 0; y1 < maze->height; y1++) {
        for (int y2 = 0; y2 < maze->height; y2++) {
            Cell start = new_cell(0, y1);
            Cell end = new_cell(maze->width - 1, y2);
            int len = _path_length(maze, start, start, end);
            if (len > longest) {
                maze->entrance = start;
                maze->exit = end;
                longest = len;
            }
        }
    }
}