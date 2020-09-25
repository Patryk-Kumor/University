fn solution(n: f64) -> f64 {
    if n.fract() < 0.25 {  n.trunc() }
    else if n.fract() < 0.75 {  n.trunc() + 0.5 }
    else { n.trunc() + 1.0 }
}

#[test]
fn test0() { assert_eq!(solution(0.000001), 0.0); }
#[test]
fn test1() { assert_eq!(solution(0.2), 0.0); }
#[test]
fn test2() { assert_eq!(solution(0.49), 0.5); }
#[test]
fn test3() { assert_eq!(solution(0.5), 0.5); }
#[test]
fn test4() { assert_eq!(solution(0.51), 0.5); }
#[test]
fn test5() { assert_eq!(solution(0.74), 0.5); }
#[test]
fn test6() { assert_eq!(solution(123321.22), 123321.0); }
#[test]
fn test7() { assert_eq!(solution(1111111111.5), 1111111111.5); }
#[test]
fn test8() { assert_eq!(solution(123456.123456), 123456.0); }
#[test]
fn test9() { assert_eq!(solution(99.99), 100.0); }


fn main() {
}
