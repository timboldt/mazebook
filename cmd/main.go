package main

import (
	"image/png"
	"os"

	maze "github.com/timboldt/mazebook"
)

func main() {
	m := maze.NewRectangularMaze(15, 30)
	m.ApplyBinaryTree()
	m.FindBestExitPoint()
	f, _ := os.Create("image_binarytree.png")
	png.Encode(f, m.ToImage())

	m = maze.NewRectangularMaze(15, 30)
	m.ApplySideWinder()
	m.FindBestExitPoint()
	f, _ = os.Create("image_sidewinder.png")
	png.Encode(f, m.ToImage())
}
