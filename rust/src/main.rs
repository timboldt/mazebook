mod maze;

fn main() {
    let m = maze::Maze::new("test", 20, 20);
    println!("maze info: {:?}", m.cell_has_connections(maze::Cell { x: 6, y: 6 }));
    m.print_to_console();
}
