use std::fs::read_to_string;

fn main() {
    // let test_input = [199, 200, 208, 210, 200, 207, 240, 269, 260, 263];
    let input: Vec<usize> = read_to_string("../input/input.txt")
        .expect("Failed to read the input data.")
        .lines()
        .map(|l| l.parse().unwrap())
        .collect();

    let mut increment = 0;
    
    for element in 1..input.len() {
        if input[element] > input[element - 1] {
            increment += 1;
        }
    }
    println!("Part 1: {}", increment);

    increment = 0;
    for element in 3..input.len() {
        if input[element] > input[element - 3] {
            increment += 1;
        }
    }
    println!("Part 1: {}", increment);
}
