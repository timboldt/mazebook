package main

import (
	"fmt"
	"image/png"
	"os"

	"github.com/timboldt/mazebook/rectangular"
)

func main() {
	var m *rectangular.Maze

	// fmt.Println("Binary Tree")
	// m = rectangular.NewMaze(50, 30)
	// m.ApplyBinaryTree()
	// m.FindBestExitPoint()
	// f, _ := os.Create("image_binarytree.png")
	// png.Encode(f, m.ToImage())

	// fmt.Println("Sidewinder")
	// m = rectangular.NewMaze(50, 30)
	// m.ApplySideWinder()
	// m.FindBestExitPoint()
	// f, _ = os.Create("image_sidewinder.png")
	// png.Encode(f, m.ToImage())

	fmt.Println("Aldous-Broder")
	m = rectangular.NewMaze(50, 30)
	m.ApplyAldousBroder()
	m.FindBestExitPoint()
	m.Print()
	f, _ := os.Create("image_aldousbroder.png")
	png.Encode(f, m.ToImage())
}
