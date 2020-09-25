fn last_digit(str1: &str, str2: &str) -> i32 {
    let a: i32 = (str1.to_string().pop().unwrap() as i32) - 48;
    let b: i32;
    if str2.len() > 1 { 
        b = str2.to_string().split_off(str2.len() - 2).parse::<i32>().unwrap(); 
    }
    else { 
        b = (str2.to_string().pop().unwrap() as i32) - 48; 
    }
    if str2.to_string() == "0" { return 1; }
    let exp: i32;
    if b % 4 == 0 {
        exp = 4; 
    }
    else {
        exp = b % 4; 
    }
    return a.pow(exp as u32) % 10;  
}

#[test]
fn test0() {
  assert_eq!(last_digit("0", "0"), 1);
}
#[test]
fn test1() {
  assert_eq!(last_digit("0", "1"), 0);
}
#[test]
fn test2() {
  assert_eq!(last_digit("0", "123"), 0);
}
#[test]
fn test3() {
  assert_eq!(last_digit("123", "0"), 1);
}
#[test]
fn test4() {
  assert_eq!(last_digit("12345", "1"), 5);
}
#[test]
fn test5() {
  assert_eq!(last_digit("4", "1"), 4);
}
#[test]
fn test6() {
  assert_eq!(last_digit("4", "2"), 6);
}

#[test]
fn test7() {
  assert_eq!(last_digit("9", "7"), 9);
}
#[test]
fn test8() {
  assert_eq!(last_digit("10", "10000000000000000"), 0);
}
#[test]
fn test9() {
  assert_eq!(last_digit("3715290469715693021198967285016729344580685479654510946723", "68819615221552997273737174557165657483427362207517952651"), 7);
}

fn main() {

}
