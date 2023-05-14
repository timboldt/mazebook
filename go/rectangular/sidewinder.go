package rectangular

import "math/rand"

func (m *Maze) ApplySideWinder() {
	m.name = "Sidewinder"
	for r := 0; r < m.rows; r++ {
		var run []cell
		for c := 0; c < m.cols; c++ {
			thisCell := Cell(r, c)

			run = append(run, thisCell)

			eastIsValid := m.IsValidCell(thisCell.East())
			southIsValid := m.IsValidCell(thisCell.South())
			endOfRun := rand.Intn(2) == 0
			shouldCloseOut := !eastIsValid || (endOfRun && southIsValid)

			if shouldCloseOut {
				// Pick a random entry from the run.
				src := run[rand.Intn(len(run))]
				// Link to the next row from the random cell.
				m.Connect(src, src.South())
				run = nil
			} else {
				// Link to next column.
				m.Connect(thisCell, thisCell.East())
			}
		}
	}
}
