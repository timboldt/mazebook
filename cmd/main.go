package main

import (
	"image/png"
	"os"

	"github.com/timboldt/mazebook/rectangular"
)

func main() {
	m := rectangular.NewMaze(15, 30)
	m.ApplyBinaryTree()
	m.FindBestExitPoint()
	f, _ := os.Create("image_binarytree.png")
	png.Encode(f, m.ToImage())

	m = rectangular.NewMaze(15, 30)
	m.ApplySideWinder()
	m.FindBestExitPoint()
	f, _ = os.Create("image_sidewinder.png")
	png.Encode(f, m.ToImage())
}
