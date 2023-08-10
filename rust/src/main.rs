mod rectangular_maze;

fn main() {
    let m = rectangular_maze::Maze::new("test", 20, 20);
    println!("maze info: {:?}", m.cell_has_connections(rectangular_maze::Cell { x: 6, y: 6 }));
    m.print_to_console();
}
