use std::collections::HashSet;

mod cell;
mod edge;

pub use cell::Cell;
pub use edge::Edge;

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
        if width < 1 || width > 200 || height < 1 || height > 200 {
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

    pub fn has_cell(&self, c: &Cell) -> bool {
        self.cells.contains(c)
    }

    pub fn cell_has_connections(&self, c: Cell) -> bool {
        self.has_edge(&Edge::new(c, c.north()))
            || self.has_edge(&Edge::new(c, c.east()))
            || self.has_edge(&Edge::new(c, c.south()))
            || self.has_edge(&Edge::new(c, c.west()))
    }

    pub fn add_edge(&mut self, c1: Cell, c2: Cell) {
        if self.has_cell(&c1) && self.has_cell(&c2) {
            self.edges.insert(Edge::new(c1, c2));
        }
    }

    pub fn has_edge(&self, e: &Edge) -> bool {
        self.edges.contains(e)
    }

    // void maze_print_console(const Maze *maze);
    // void maze_save_png(const Maze *maze, const char *filename);
    // void maze_update_entrance(Maze *maze);
}
