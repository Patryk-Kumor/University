fn xo(string: &'static str) -> bool {
  let x = string.chars().collect::<Vec<char>>().iter().filter(|&e| *e == 'x' || *e == 'X').count();
  let o = string.chars().collect::<Vec<char>>().iter().filter(|&e| *e == 'o' ||  *e == 'O').count();
  x == o 
}

#[test]
fn test0() { assert_eq!(xo(""), true); }
#[test]
fn test1() { assert_eq!(xo("xo"), true); }
#[test]
fn test2() { assert_eq!(xo("xxoo"), true); }
#[test]
fn test3() { assert_eq!(xo("XO"), true); }
#[test]
fn test4() { assert_eq!(xo("xo"), true); }
#[test]
fn test5() { assert_eq!(xo("Ox"), true); }
#[test]
fn test6() { assert_eq!(xo("abc"), true); }
#[test]
fn test7() { assert_eq!(xo("abcxo"), true); }
#[test]
fn test8() { assert_eq!(xo("xxo"), false); }
#[test]
fn test9() { assert_eq!(xo("oox"), false); }

fn main() {
}
