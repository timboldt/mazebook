use std::cmp::Ordering;

use super::Cell;

// An Edge represents a bi-directional connection between two Cells in a Maze.
#[derive(Copy, Clone, Debug, PartialEq, Eq, Hash)]
pub struct Edge {
    c1: Cell,
    c2: Cell,
}

impl Edge {
    pub fn new(a: Cell, b: Cell) -> Edge {
        match a.cmp(&b) {
            Ordering::Greater => Edge { c1: b, c2: a },
            Ordering::Less => Edge { c1: a, c2: b },
            Ordering::Equal => panic!("An edge cannot be self-referential."),
        }
    }
}
