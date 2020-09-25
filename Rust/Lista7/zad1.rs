fn chessboard_cell_color(cell1: &str, cell2: &str) -> bool {
    let mut x: i32 = 0;
    let mut y: i32 = 0;
    let mut k1: i32 = 0;
    let mut k2: i32 = 0;
   
    x = cell1.chars().next().unwrap() as i32 - 'A' as i32 - 1;
    y = cell1.chars().last().unwrap() as i32 - '1' as i32 - 1;
    k1 = (x + y) % 2;    
    
    x = cell2.chars().next().unwrap() as i32 - 'A' as i32 - 1;
    y = cell2.chars().last().unwrap() as i32 - '1' as i32 - 1 ;
    k2 = (x + y) % 2;    
    
    k1 == k2
}

#[test]
fn test0() {
    assert!(chessboard_cell_color("A1", "A1"));
}
#[test]
fn test1() {
    assert!(!chessboard_cell_color("A1", "A2"));
}
#[test]
fn test2() {
    assert!(chessboard_cell_color("A1", "A3"));
}
#[test]
fn test3() {
    assert!(!chessboard_cell_color("C1", "A2"));
}
#[test]
fn test4() {
    assert!(!chessboard_cell_color("B1", "D6"));
}
#[test]
fn test5() {
    assert!(chessboard_cell_color("D6", "D6"));
}
#[test]
fn test6() {
    assert!(!chessboard_cell_color("C1", "A2"));
}
#[test]
fn test7() {
    assert!(chessboard_cell_color("B1", "A2"));
}
#[test]
fn test8() {
    assert!(!chessboard_cell_color("A1", "C2"));
}
#[test]
fn test9() {
    assert!(!chessboard_cell_color("E1", "A2"));
}

fn main() {
}
