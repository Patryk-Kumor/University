fn find_digit(num: i32, nth: i32) -> i32 {
    if nth <= 0 {return -1;} let mut num = num.abs(); let mut nth = nth;
    loop { if nth == 1 {return num % 10; } num /= 10; nth -= 1; }
}



#[test]
fn test0() {
  assert_eq!(find_digit(0, 0), -1);
}

#[test]
fn test1() {
  assert_eq!(find_digit(0, 1), 0);
}
#[test]
fn test2() {
  assert_eq!(find_digit(-1, 1), 1);
}
#[test]
fn test3() {
  assert_eq!(find_digit(-1, 2), 0);
}
#[test]
fn test4() {
  assert_eq!(find_digit(5673, 4), 5);
}
#[test]
fn test5() {
  assert_eq!(find_digit(129, 2), 2);
}
#[test]
fn test6() {
  assert_eq!(find_digit(-2825, 3), 8);
}
#[test]
fn test7() {
  assert_eq!(find_digit(-456, 4), 0);
}
#[test]
fn test8() {
  assert_eq!(find_digit(0, 20), 0);
}
#[test]
fn test9() {
  assert_eq!(find_digit(65, 0), -1);
}

fn main() {
}
