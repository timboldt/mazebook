package rectangular

import "math/rand"

func (m *Maze) ApplySideWinder() {
	m.name = "Sidewinder"
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
