fn game(n: u64) -> Vec<u64> {
    let x: u64 = n * n;
    if x % 2 == 0 {
        vec![x / 2]
    }
    else {
        vec![x, 2]
    }
}

#[test]
fn test0() {
    assert_eq!(game(1), vec![1,2]);
}
#[test]
fn test1() {
    assert_eq!(game(2), vec![2]);
}
#[test]
fn test2() {
    assert_eq!(game(3), vec![9,2]);
}
#[test]
fn test3() {
    assert_eq!(game(4), vec![8]);
}
#[test]
fn test4() {
    assert_eq!(game(5), vec![25,2]);
}
#[test]
fn test5() {
    assert_eq!(game(6), vec![18]);
}
#[test]
fn test6() {
    assert_eq!(game(7), vec![49,2]);
}
#[test]
fn test7() {
    assert_eq!(game(8), vec![32]);
}
#[test]
fn test8() {
    assert_eq!(game(9), vec![81,2]);
}
#[test]
fn test9() {
    assert_eq!(game(10), vec![50]);
}

fn main() {
}
