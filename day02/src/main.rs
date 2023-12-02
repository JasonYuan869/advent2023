use std::fs;

fn part1(contents: &str) -> i32 {
    const RED_COUNT: i32 = 12;
    const GREEN_COUNT: i32 = 13;
    const BLUE_COUNT: i32 = 14;

    let mut lines = contents.lines();
    let mut ret = 0;
    'line_loop: loop {
        if let Some(line) = lines.next() {
            let mut parsed_line = line.split(": ");
            let game_id = parsed_line
                .next().unwrap()
                .split_whitespace()
                .nth(1).unwrap()
                .parse::<i32>().unwrap();

            let parsed_trials = parsed_line
                .next().unwrap()
                .split("; ");

            for trial in parsed_trials {
                let parsed_cubes = trial.split(", ");
                for cube in parsed_cubes {
                    let tokens: Vec<&str> = cube.split_whitespace().collect();
                    let count = tokens[0].parse::<i32>().unwrap();
                    let limit = match tokens[1] {
                        "red" => RED_COUNT,
                        "green" => GREEN_COUNT,
                        "blue" => BLUE_COUNT,
                        _ => panic!("unrecognized colour"),
                    };
                    if count > limit {
                        continue 'line_loop;
                    }
                }
            }

            ret += game_id;
        } else {
            break;
        }
    }
    ret
}

fn part2(contents: &str) -> i32 {
    let lines = contents.lines();
    let mut ret = 0;
    for line in lines {
        let mut parsed_line = line.split(": ");
        let _game_id = parsed_line
            .next().unwrap()
            .split_whitespace()
            .nth(1).unwrap()
            .parse::<i32>().unwrap();

        let parsed_trials = parsed_line
            .next().unwrap()
            .split("; ");

        let mut min_red = 0;
        let mut min_green = 0;
        let mut min_blue = 0;

        for trial in parsed_trials {
            let parsed_cubes = trial.split(", ");
            for cube in parsed_cubes {
                let tokens: Vec<&str> = cube.split_whitespace().collect();
                let count = tokens[0].parse::<i32>().unwrap();
                match tokens[1] {
                    "red" => min_red = std::cmp::max(count, min_red),
                    "green" => min_green = std::cmp::max(count, min_green),
                    "blue" => min_blue = std::cmp::max(count, min_blue),
                    _ => panic!("unrecognized colour")
                }
            }
        }
        let power = min_red * min_blue * min_green;
        ret += power;
    }
    ret

}

fn main() {
    let path = std::env::args().nth(1).expect("expected a path as the first argument");
    let contents = fs::read_to_string(path).expect("unable to read file");
    println!("{}", part1(&contents));
    println!("{}", part2(&contents));
}
