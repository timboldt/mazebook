mod rectangular_maze;

fn main() {
    let mut m = rectangular_maze::Maze::new("test", 20, 20);
    rectangular_maze::apply_aldous_broder(&mut m);
    rectangular_maze::Maze::maze_update_entrance(&mut m);
    rectangular_maze::print_to_console(&m);
}
