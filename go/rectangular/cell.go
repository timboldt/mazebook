package rectangular

type cell struct {
	row int
	col int
}

func Cell(row, col int) cell {
	return cell{row: row, col: col}
}

func (c cell) Hash() int {
	return CellHash(c)
}

func (c cell) North() cell {
	return cell{c.row - 1, c.col}
}

func (c cell) South() cell {
	return cell{c.row + 1, c.col}
}

func (c cell) East() cell {
	return cell{c.row, c.col + 1}
}

func (c cell) West() cell {
	return cell{c.row, c.col - 1}
}

func CellHash(c cell) int {
	return c.row*1e3 + c.col
}
