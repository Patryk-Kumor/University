fn descending_order(x: u64) -> u64 {
    let mut chars: Vec<char> = x.to_string().chars().collect();
    chars.sort(); chars.reverse();
    let s: String = chars.into_iter().collect();
    s.parse::<u64>().unwrap()
}


#[test]
fn test0() { assert_eq!(descending_order(0), 0); }
#[test]
fn test1() { assert_eq!(descending_order(1), 1); }
#[test]
fn test2() { assert_eq!(descending_order(11), 11); }
#[test]
fn test3() { assert_eq!(descending_order(111), 111); }
#[test]
fn test4() { assert_eq!(descending_order(123), 321); }
#[test]
fn test5() { assert_eq!(descending_order(101), 110); }
#[test]
fn test6() { assert_eq!(descending_order(1021), 2110); }
#[test]
fn test7() { assert_eq!(descending_order(123456789), 987654321); }
#[test]
fn test8() { assert_eq!(descending_order(123456789123456789), 998877665544332211); }
#[test]
fn test9() { assert_eq!(descending_order(25), 52); }



fn main() {

}
