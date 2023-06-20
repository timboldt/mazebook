use crate::maze::Cell;

// An Edge represents a bi-directional connection between two Cells in a Maze.
#[derive(Debug, PartialEq, Eq, Hash)]
pub struct Edge {
    c1: Cell,
    c2: Cell,
}

impl Edge {
    pub fn new(a: Cell, b: Cell) -> Edge {
        if a < b {
            Edge { c1: a, c2: b }
        } else if b < a {
            Edge { c1: b, c2: a }
        } else {
            panic!("An edge cannot be self-referential.");
        }
    }
}
