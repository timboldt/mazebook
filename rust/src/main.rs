mod maze;

fn main() {
    let c = maze::Cell { x: 32, y: 42 };
    println!("cell info: {:?}", c.north().south().east().west());
    let e = maze::Edge::new(c, maze::Cell { x: 1, y: 2 });
    println!("edge info: {:?}", e)
}
