package rectangular

import "math/rand"

func (m *Maze) ApplyBinaryTree() {
	m.name = "Binary Tree"
	for r := 0; r < m.rows; r++ {
		for c := 0; c < m.cols; c++ {
			thisCell := Cell(r, c)
			south := thisCell.South()
			east := thisCell.East()

			// Pick between linking vertically or horizontally.
			rnd := rand.Intn(2)
			if !(m.IsValidCell(east) || m.IsValidCell(south)) {
				// Neither will work.
				rnd = -1
			} else if !m.IsValidCell(south) {
				// Linking rows won't work, so use columns.
				rnd = 1
			} else if !m.IsValidCell(east) {
				// Linking columns won't work, so use rows.
				rnd = 0
			}
			switch rnd {
			case 0:
				// Link to next row.
				m.Connect(thisCell, south)
			case 1:
				// Link to next column.
				m.Connect(thisCell, east)
			}
		}
	}
}
