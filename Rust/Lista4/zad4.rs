fn my_first_interpreter(code: &str) -> String {
    let input: Vec<char> = code.to_string().chars().collect();
    let mut output: String = String::new();
    let mut cell: u8 = 0;
    for elem in input {
        match elem {
            '+' => { cell = cell.wrapping_add(1); },
            '.' => { output.push(cell as char); },
            _ => {}
        }
    }
    output
}

#[test]
fn test0() {
    assert_eq!(my_first_interpreter("+++++++++++++++++++++++++++++++++."), "!");
}
#[test]
fn test1() {
    assert_eq!(my_first_interpreter("+++++++++++++++++++++++++++++++++..."), "!!!");
}
#[test]
fn test2() {
    assert_eq!(my_first_interpreter("+++++++++++++++++++++++++++++++++......"), "!!!!!!");
}
#[test]
fn test3() {
    assert_eq!(my_first_interpreter("++++++++++++++++++++++++++++++++++++++.+.+.+.+.+.....+.+.+.+.."), "&'()*+++++,-.//");
}
#[test]
fn test4() {
    assert_eq!(my_first_interpreter("++++++++++++++++++++++++++++++++++++++++++++++++++++++++......"), "888888");
}
#[test]
fn test5() {
    assert_eq!(my_first_interpreter("++++++++++++++++++++++++++++++++++++++++++++++++..-.-..-.-.-.-.-..-.-.-."), "00000000000000");
}
#[test]
fn test6() {
    assert_eq!(my_first_interpreter("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++abcdefgh."), "A");
}
#[test]
fn test7() {
    assert_eq!(my_first_interpreter("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++."), "A");
}
#[test]
fn test8() {
    assert_eq!(my_first_interpreter("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++......"), "AAAAAA");
}
#[test]
fn test9() {
    assert_eq!(my_first_interpreter("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.+..+...+.+..++."), "ABBCCCDEEG");
}

fn main() {
}
