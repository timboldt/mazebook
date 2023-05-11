package main

import (
	"fmt"

	maze "github.com/timboldt/mazebook"
)

func main() {
	m := maze.NewRectangularMaze(5, 10)
	fmt.Printf("%+v", m)
}
