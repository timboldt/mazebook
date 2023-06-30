mod maze;

fn main() {
    let m = maze::Maze::new("test", 32, 42);
    println!("maze info: {:?}", m.cell_has_connections(maze::Cell { x: 6, y: 6 }));
}
