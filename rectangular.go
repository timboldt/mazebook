package maze

import (
	"fmt"
	"math/rand"

	"github.com/dominikbraun/graph"
)

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
		}
	}
	return m
}

func (m *RectangularMaze) GetCell(row, col int) (Cell, error) {
	return m.g.Vertex(CellHash(Cell{row: row, col: col}))
}

func (m *RectangularMaze) String() string {
	return fmt.Sprintf("RectMaze[%d, %d]: %+v", m.rows, m.cols, m.g)
}

// func (m *RectangularMaze) DrawSVG() {
// 	file, _ := os.Create("./mygraph.gv")
// 	defer file.Close()
// 	_ = draw.DOT(m.g, file)
// }

func (m *RectangularMaze) Print() {
	fmt.Print("+")
	for c := 0; c < m.cols; c++ {
		fmt.Print("---+")
	}
	fmt.Println()

	for r := 0; r < m.rows; r++ {
		body := "|"
		bottom := "+"
		for c := 0; c < m.cols; c++ {
			body += "   "
			if _, err := m.g.Edge(CellHash(Cell{row: r, col: c}), CellHash(Cell{row: r, col: c + 1})); err == nil {
				body += " "
			} else {
				body += "|"
			}

			if _, err := m.g.Edge(CellHash(Cell{row: r, col: c}), CellHash(Cell{row: r + 1, col: c})); err == nil {
				bottom += "   "
			} else {
				bottom += "---"
			}
			bottom += "+"
		}
		fmt.Println(body)
		fmt.Println(bottom)
	}
}

func (m *RectangularMaze) ApplyBinaryTree() {
	for r := 0; r < m.rows; r++ {
		for c := 0; c < m.cols; c++ {
			// Pick between linking vertically or horizontally.
			rnd := rand.Intn(2)
			if r+1 == m.rows && c+1 == m.cols {
				// Neither will work.
				rnd = -1
			} else if r+1 == m.rows {
				// Linking rows won't work, so use columns.
				rnd = 1
			} else if c+1 == m.cols {
				// Linking columns won't work, so use rows.
				rnd = 0
			}
			switch rnd {
			case 0:
				// Link to next row.
				m.g.AddEdge(
					CellHash(Cell{row: r, col: c}),
					CellHash(Cell{row: r + 1, col: c}),
				)
			case 1:
				// Link to next column.
				m.g.AddEdge(
					CellHash(Cell{row: r, col: c}),
					CellHash(Cell{row: r, col: c + 1}),
				)
			}
		}
	}
}

func (m *RectangularMaze) ApplySideWinder() {
	for r := 0; r < m.rows; r++ {
		var run []Cell
		for c := 0; c < m.cols; c++ {
			run = append(run, Cell{row: r, col: c})

			shouldCloseOut := c+1 == m.cols || (rand.Intn(2) == 0 && r+1 != m.rows)

			if shouldCloseOut {
				// Pick a random entry from the run.
				src := run[rand.Intn(len(run))]
				// Link to the next row from the random cell.
				m.g.AddEdge(
					CellHash(src),
					CellHash(Cell{row: src.row + 1, col: src.col}),
				)
				run = nil
			} else {
				// Link to next column.
				m.g.AddEdge(
					CellHash(Cell{row: r, col: c}),
					CellHash(Cell{row: r, col: c + 1}),
				)
			}
		}
	}
}
