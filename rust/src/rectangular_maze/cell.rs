// A Cell represents a location in the Maze. It can also be thought of as a node
// in a graph.
#[derive(Copy, Clone, Debug, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub struct Cell {
    pub x: i16,
    pub y: i16,
}

impl Cell {
    pub fn north(&self) -> Cell {
        Cell {
            x: self.x,
            y: self.y + 1,
        }
    }
    pub fn east(&self) -> Cell {
        Cell {
            x: self.x + 1,
            y: self.y,
        }
    }
    pub fn south(&self) -> Cell {
        Cell {
            x: self.x,
            y: self.y - 1,
        }
    }
    pub fn west(&self) -> Cell {
        Cell {
            x: self.x - 1,
            y: self.y,
        }
    }
}
