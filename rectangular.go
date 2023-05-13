package maze

import (
	"fmt"
	"image"
	"log"
	"math/rand"

	"github.com/dominikbraun/graph"
	"github.com/fogleman/gg"
	"github.com/golang/freetype/truetype"
	"golang.org/x/image/font/gofont/goregular"
)

type RectangularMaze struct {
	name string

	rows int
	cols int

	start, end Cell

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
		rows:  rows,
		cols:  cols,
		start: Cell{row: rows / 2, col: cols / 2},
		end:   Cell{row: rows - 1, col: cols - 1},
		g:     graph.New(CellHash),
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
			if r == m.start.row && c == m.start.col {
				body += " S "
			} else if r == m.end.row && c == m.end.col {
				body += " E "
			} else {
				body += "   "
			}
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

func (m *RectangularMaze) ToImage() image.Image {
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

	dc.SetFontFace(truetype.NewFace(font, &truetype.Options{Size: 80}))
	dc.SetRGBA(0, 0, 0, 0.25)
	dc.DrawStringAnchored(m.name, float64(dc.Width())/2, float64(dc.Height())/2, 0.5, 0.5)

	dc.SetRGBA(0, 0, 0, 1)
	dc.SetLineCap(gg.LineCapRound)
	dc.SetLineWidth(5)

	dc.DrawLine(0, 0, float64(dc.Width()), 0)
	dc.Stroke()

	dc.DrawLine(0, 0, 0, float64(dc.Height()))
	dc.Stroke()

	dc.SetFontFace(truetype.NewFace(font, &truetype.Options{Size: 6}))
	for r := 0; r < m.rows; r++ {
		for c := 0; c < m.cols; c++ {
			cellLeft := float64(c * cellSize)
			cellTop := float64(r * cellSize)

			if r == m.start.row && c == m.start.col {
				dc.SetRGBA(0, 0.5, 0, 0.5)
				dc.DrawCircle(cellLeft+0.5*cellSize, cellTop+0.5*cellSize, cellSize*0.35)
				dc.Fill()
				dc.SetRGBA(0, 0, 0, 1)
				dc.DrawStringAnchored("Start", cellLeft+0.5*cellSize, cellTop+0.5*cellSize, 0.5, 0.5)
			} else if r == m.end.row && c == m.end.col {
				dc.SetRGBA(0.5, 0, 0.5, 0.5)
				dc.DrawCircle(cellLeft+0.5*cellSize, cellTop+0.5*cellSize, cellSize*0.35)
				dc.Fill()
				dc.SetRGBA(0, 0, 0, 1)
				dc.DrawStringAnchored("End", cellLeft+0.5*cellSize, cellTop+0.5*cellSize, 0.5, 0.5)
			}

			dc.SetRGBA(0, 0, 0, 1)
			if _, err := m.g.Edge(CellHash(Cell{row: r, col: c}), CellHash(Cell{row: r, col: c + 1})); err != nil {
				dc.DrawLine(float64((c+1)*cellSize), float64(r*cellSize)+1, float64((c+1)*cellSize), float64((r+1)*cellSize)-1)
				dc.Stroke()
			}
			if _, err := m.g.Edge(CellHash(Cell{row: r, col: c}), CellHash(Cell{row: r + 1, col: c})); err != nil {
				dc.DrawLine(float64(c*cellSize)+1, float64((r+1)*cellSize), float64((c+1)*cellSize)-1, float64((r+1)*cellSize))
				dc.Stroke()
			}
		}
	}

	return dc.Image()
}

func (m *RectangularMaze) FindBestExitPoint() {
	path, _ := graph.ShortestPath(m.g, CellHash(m.start), CellHash(m.end))
	best := len(path)
	for r := 0; r < m.rows; r++ {
		for c := 0; c < m.cols; c++ {
			path, _ = graph.ShortestPath(m.g, CellHash(Cell{row: r, col: c}), CellHash(m.end))
			newLen := len(path)
			if newLen > best {
				m.start = Cell{row: r, col: c}
				best = newLen
			}
		}
	}
}

func (m *RectangularMaze) ApplyBinaryTree() {
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

func (m *RectangularMaze) ApplySideWinder() {
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
