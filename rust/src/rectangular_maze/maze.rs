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

    pub fn print_to_console(&self) {
        print!("+");
        for _ in 0..self.width {
            print!("---+");
        }
        println!();

        // Note: `y` grows from bottom to top, so we need to go in reverse.
        for y in (0..self.height).rev() {
            let mut middle = "|".to_string();
            let mut bottom = "+".to_string();
            for x in 0..self.width {
                let this_cell = Cell { x, y };
                if this_cell == self.entrance {
                    middle.push_str(" S ");
                } else if this_cell == self.exit {
                    middle.push_str(" E ");
                } else {
                    middle.push_str("   ");
                }
                if self.has_edge(this_cell, this_cell.east()) {
                    middle.push(' ');
                } else {
                    middle.push('|');
                }
                if self.has_edge(this_cell, this_cell.south()) {
                    bottom.push_str("   +");
                } else {
                    bottom.push_str("---+");
                }
            }
            println!("{}", middle);
            println!("{}", bottom);
        }
    }
    // void maze_save_png(const Maze *maze, const char *filename);
    // void maze_update_entrance(Maze *maze);
}
