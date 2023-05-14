package rectangular

import (
	"math/rand"
)

func (m *Maze) ApplyAldousBroder() {
	m.name = "Aldous-Broder"
	thisCell := Cell(rand.Intn(m.rows), rand.Intn(m.cols))
	unvisited := m.rows*m.cols - 1

	for unvisited > 0 {
		var neighbor cell
		direction := rand.Intn(4)
		switch direction {
		case 0:
			neighbor = thisCell.North()
		case 1:
			neighbor = thisCell.East()
		case 2:
			neighbor = thisCell.South()
		case 3:
			neighbor = thisCell.West()
		}
		if m.IsValidCell(neighbor) {
			if !m.HasConnection(neighbor) {
				m.Connect(thisCell, neighbor)
				unvisited--
			}
			thisCell = neighbor
		}
	}
}
