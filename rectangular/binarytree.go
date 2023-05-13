package rectangular

import "math/rand"

func (m *Maze) ApplyBinaryTree() {
	m.name = "Binary Tree"
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
