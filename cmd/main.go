package main

import (
	"image/png"
	"os"

	maze "github.com/timboldt/mazebook"
)

func main() {
	m1 := maze.NewRectangularMaze(15, 30)
	m1.ApplyBinaryTree()
	//m1.Print()
	f, _ := os.Create("image1.png")
	png.Encode(f, m1.ToImage())

	m2 := maze.NewRectangularMaze(15, 30)
	m2.ApplySideWinder()
	//m2.Print()
	f, _ = os.Create("image2.png")
	png.Encode(f, m2.ToImage())
}
