package maze

import "github.com/dominikbraun/graph"

type RectangularMaze struct {
	rows int
	cols int

	g graph.Graph[int, Cell]
}

type Cell struct {
	row int
	col int
}

func CellHash(c Cell) int {
	return c.row*1e6 + c.col
}

func NewRectangularMaze(rows, cols int) *RectangularMaze {
	m := &RectangularMaze{
		rows: rows,
		cols: cols,
		g:    graph.New(CellHash),
	}
	for r := 0; r < rows; r++ {
		for c := 0; c < cols; c++ {
			m.g.AddVertex(Cell{row: r, col: c})
			if r > 0 {
				m.g.AddEdge(
					CellHash(Cell{row: r, col: c}),
					CellHash(Cell{row: r - 1, col: c}),
				)
			}
			if c > 0 {
				m.g.AddEdge(
					CellHash(Cell{row: r, col: c}),
					CellHash(Cell{row: r, col: c - 1}),
				)
			}
		}
	}
	return m
}
