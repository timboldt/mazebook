package rectangular

import "math/rand"

func (m *Maze) ApplySideWinder() {
	m.name = "Sidewinder"
	for r := 0; r < m.rows; r++ {
		var run []cell
		for c := 0; c < m.cols; c++ {
			run = append(run, cell{row: r, col: c})

			shouldCloseOut := c+1 == m.cols || (rand.Intn(2) == 0 && r+1 != m.rows)

			if shouldCloseOut {
				// Pick a random entry from the run.
				src := run[rand.Intn(len(run))]
				// Link to the next row from the random cell.
				m.g.AddEdge(
					CellHash(src),
					CellHash(cell{row: src.row + 1, col: src.col}),
				)
				run = nil
			} else {
				// Link to next column.
				m.g.AddEdge(
					CellHash(cell{row: r, col: c}),
					CellHash(cell{row: r, col: c + 1}),
				)
			}
		}
	}
}
