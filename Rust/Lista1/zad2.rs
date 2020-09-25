fn string_to_number(s: &str) -> i32 {
   s.parse::<i32>().unwrap()
}

#[test]
fn test0() {
   assert_eq!(string_to_number("1234"), 1234);
}
#[test]
fn test1() {
   assert_eq!(string_to_number("0"), 0);
}
#[test]
fn test2() {
   assert_eq!(string_to_number("666"), 666);
}
#[test]
fn test3() {
   assert_eq!(string_to_number("-123"), -123);
}
#[test]
fn test4() {
   assert_eq!(string_to_number("-2423"), -2423);
}