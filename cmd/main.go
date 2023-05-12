package main

import (
	"fmt"

	maze "github.com/timboldt/mazebook"
)

func main() {
	m1 := maze.NewRectangularMaze(15, 30)
	m1.ApplyBinaryTree()
	m1.Print()

	fmt.Printf("\n=========================================================================================================================\n\n")

	m2 := maze.NewRectangularMaze(15, 30)
	m2.ApplySideWinder()
	m2.Print()
}
