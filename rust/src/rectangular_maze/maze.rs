use std::collections::HashSet;

use super::Cell;
use super::Edge;

#[allow(dead_code)]
pub struct Maze {
    name: String,
    width: i16,
    height: i16,
    entrance: Cell,
    exit: Cell,
    cells: HashSet<Cell>,
    edges: HashSet<Edge>,
}

impl Maze {
    pub fn new(name: &str, width: i16, height: i16) -> Maze {
        if !(1..=200).contains(&width) || !(1..=200).contains(&height) {
            panic!("Invalid maze setup");
        }
        let mut m = Maze {
            name: name.to_owned(),
            width,
            height,
            entrance: Cell { x: 0, y: 0 },
            exit: Cell {
                x: width - 1,
                y: height - 1,
            },
            cells: HashSet::new(),
            edges: HashSet::new(),
        };
        for x in 0..width {
            for y in 0..height {
                m.add_cell(Cell { x, y })
            }
        }
        m
    }

    pub fn set_name(&mut self, name: &str) {
        self.name = name.to_string();
    }

    pub fn width(&self) -> i16 {
        self.width
    }

    pub fn height(&self) -> i16 {
        self.height
    }

    pub fn entrance(&self) -> Cell {
        self.entrance
    }

    pub fn exit(&self) -> Cell {
        self.exit
    }

    pub fn add_cell(&mut self, c: Cell) {
        if c.x >= 0 && c.x < self.width && c.y >= 0 && c.y < self.height {
            self.cells.insert(c);
        }
    }

    #[allow(dead_code)]
    pub fn has_cell(&self, c: &Cell) -> bool {
        self.cells.contains(c)
    }

    pub fn cell_has_connections(&self, c: Cell) -> bool {
        self.has_edge(c, c.north())
            || self.has_edge(c, c.east())
            || self.has_edge(c, c.south())
            || self.has_edge(c, c.west())
    }

    #[allow(dead_code)]
    pub fn add_edge(&mut self, c1: Cell, c2: Cell) {
        if self.has_cell(&c1) && self.has_cell(&c2) {
            self.edges.insert(Edge::new(c1, c2));
        }
    }

    pub fn has_edge(&self, c1: Cell, c2: Cell) -> bool {
        self.edges.contains(&Edge::new(c1, c2))
    }

    fn path_length(&self, prev: Cell, curr: Cell, end: Cell) -> i32 {
        if curr == end {
            return 0;
        }
        let mut best = 9999;
        for dir in 0..4 {
            let next = match dir {
                0 => curr.north(),
                1 => curr.east(),
                2 => curr.south(),
                _ => curr.west(),
            };
            // If we are connected to the next cell and it is not the cell we came
            // from, consider it as a candidate.
            if self.has_edge(curr, next) && next != prev {
                let len = self.path_length(curr, next, end);
                if len < best {
                    best = len;
                }
            }
        }
        best + 1
    }

    pub fn maze_update_entrance(&mut self) {
        let mut longest = 0;
        // Find the entrance along the left, searching from top to bottom.
        for y1 in (0..self.height).rev() {
            // Find the exit along the right, searching from bottom to top.
            for y2 in 0..self.height {
                let start = Cell { x: 0, y: y1 };
                let end = Cell {
                    x: self.width - 1,
                    y: y2,
                };
                let len = self.path_length(start, start, end);
                if len > longest {
                    self.entrance = start;
                    self.exit = end;
                    longest = len;
                }
            }
        }
    }
}
