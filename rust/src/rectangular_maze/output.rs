use crate::rectangular_maze::{Cell, Maze};

pub fn print_to_console(m: &Maze) {
    print!("+");
    for _ in 0..m.width() {
        print!("---+");
    }
    println!();

    // Note: `y` grows from bottom to top, so we need to go in reverse.
    for y in (0..m.height()).rev() {
        let mut middle = "|".to_string();
        let mut bottom = "+".to_string();
        for x in 0..m.width() {
            let this_cell = Cell { x, y };
            if this_cell == m.entrance() {
                middle.push_str(" S ");
            } else if this_cell == m.exit() {
                middle.push_str(" E ");
            } else {
                middle.push_str("   ");
            }
            if m.has_edge(this_cell, this_cell.east()) {
                middle.push(' ');
            } else {
                middle.push('|');
            }
            if m.has_edge(this_cell, this_cell.south()) {
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
