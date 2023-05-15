#pragma once

#include "cell.h"
#include "edge.h"

#define MAX_CELLS 2048
#define MAX_EDGES (MAX_CELLS*2)

typedef struct {
    char name[80];

    int16_t width;
    int16_t height;

    Cell entrance;
    Cell exit;

    CellHash cell_set[MAX_CELLS];
    EdgeHash edge_set[MAX_EDGES];
} Maze;

void maze_init(Maze *maze, const char *name, int16_t width, int16_t height);


/*
func NewMaze(rows, cols int) *Maze {
	m := &Maze{
		rows:  rows,
		cols:  cols,
		start: Cell(rows/2, cols/2),
		end:   Cell(rows-1, cols-1),
		g:     graph.New(CellHash),
	}
	for r := 0; r < rows; r++ {
		for c := 0; c < cols; c++ {
			m.g.AddVertex(Cell(r, c))
		}
	}
	return m
}

func (m *Maze) IsValidCell(c cell) bool {
	_, err := m.g.Vertex(c.Hash())
	return err == nil
}

func (m *Maze) Connect(src, dst cell) {
	m.g.AddEdge(src.Hash(), dst.Hash())
}

func (m *Maze) IsConnected(src, dst cell) bool {
	_, err := m.g.Edge(src.Hash(), dst.Hash())
	return err == nil
}

func (m *Maze) HasConnection(c cell) bool {
	if m.IsConnected(c, c.North()) {
		return true
	}
	if m.IsConnected(c, c.East()) {
		return true
	}
	if m.IsConnected(c, c.South()) {
		return true
	}
	if m.IsConnected(c, c.West()) {
		return true
	}
	return false
}

func (m *Maze) Print() {
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

func (m *Maze) ToImage() image.Image {
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
	dc.DrawStringAnchored(m.name, float64(dc.Width())/2, float64(dc.Height())/2, 0.5, 0.5)

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
				dc.DrawCircle(cellLeft+0.5*cellSize, cellTop+0.5*cellSize, cellSize*0.35)
				dc.Fill()
				dc.SetRGBA(0, 0, 0, 1)
				dc.SetFontFace(truetype.NewFace(font, &truetype.Options{Size: 6}))
				dc.DrawStringAnchored("Start", cellLeft+0.5*cellSize, cellTop+0.5*cellSize, 0.5, 0.5)
			} else if r == m.end.row && c == m.end.col {
				dc.SetRGBA(0.5, 0, 0.5, 0.5)
				dc.DrawCircle(cellLeft+0.5*cellSize, cellTop+0.5*cellSize, cellSize*0.35)
				dc.Fill()
				dc.SetRGBA(0, 0, 0, 1)
				dc.SetFontFace(truetype.NewFace(font, &truetype.Options{Size: 6}))
				dc.DrawStringAnchored("End", cellLeft+0.5*cellSize, cellTop+0.5*cellSize, 0.5, 0.5)
			}

			// Restore line color and draw right and bottom sides of cell, as required.
			dc.SetRGBA(0, 0, 0, 1)
			if !m.IsConnected(thisCell, thisCell.East()) {
				dc.DrawLine(float64((c+1)*cellSize), float64(r*cellSize)+1, float64((c+1)*cellSize), float64((r+1)*cellSize)-1)
				dc.Stroke()
			}
			if !m.IsConnected(thisCell, thisCell.South()) {
				dc.DrawLine(float64(c*cellSize)+1, float64((r+1)*cellSize), float64((c+1)*cellSize)-1, float64((r+1)*cellSize))
				dc.Stroke()
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