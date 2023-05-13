package rectangular

import (
	"math/rand"
)

func (m *Maze) visited(r, c int) bool {
	var nr, nc int
	for direction := 0; direction < 4; direction++ {
		switch direction {
		case 0:
			nr, nc = r+1, c
		case 1:
			nr, nc = r-1, c
		case 2:
			nr, nc = r, c+1
		case 3:
			nr, nc = r, c-1
		}
		src := CellHash(cell{row: r, col: c})
		dest := CellHash(cell{row: nr, col: nc})
		// _, err := m.g.Edge(src, dest)
		// fmt.Printf("%d - %d: %v\n", src, dest, err)
		if _, err := m.g.Edge(src, dest); err == nil {
			return true
		}
	}
	return false
}

func (m *Maze) ApplyAldousBroder() {
	m.name = "Aldous-Broder"
	r := rand.Intn(m.rows)
	c := rand.Intn(m.cols)
	unvisited := m.rows*m.cols - 1

	for unvisited > 0 {
		direction := rand.Intn(4)
		var nr, nc int
		switch direction {
		case 0:
			nr, nc = r+1, c
		case 1:
			nr, nc = r-1, c
		case 2:
			nr, nc = r, c+1
		case 3:
			nr, nc = r, c-1
		}
		if nr >= 0 && nr < m.rows && nc >= 0 && nc < m.cols {
			//fmt.Printf("(%d,%d): %v\n", nr, nc, m.visited(nr, nc))
			if !m.visited(nr, nc) {
				src := CellHash(cell{row: r, col: c})
				dest := CellHash(cell{row: nr, col: nc})
				m.g.AddEdge(src, dest)
				unvisited--
			}

			r = nr
			c = nc
		}
	}
}
