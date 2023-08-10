use rand::Rng;

use crate::rectangular_maze::{Cell, Maze};

pub fn apply_aldous_broder(m: &mut Maze) {
    let mut rng = rand::thread_rng();

    m.set_name("Aldous-Broder");
    let mut cell = Cell {
        x: rng.gen_range(0..m.width()),
        y: rng.gen_range(0..10),
    };
    let mut unvisited = m.width() * m.height() - 1;
    while unvisited > 0 {
        let neighbor = match rng.gen_range(0..4) {
            0 => cell.north(),
            1 => cell.east(),
            2 => cell.south(),
            _ => cell.west(),
        };
        if m.has_cell(&neighbor) {
            if !m.cell_has_connections(neighbor) {
                m.add_edge(cell, neighbor);
                unvisited -= 1;
            }
            cell = neighbor;
        }
    }
}
