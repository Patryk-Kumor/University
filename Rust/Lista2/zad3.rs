fn summy(strng: &str) -> i32 {
    let nums: Vec<&str> = strng.split(" ").collect();
    let mut sum = 0;
    for elem in nums{
        sum += elem.parse::<i32>().unwrap();
    }
    sum
}

#[test]
fn test0() {
   assert_eq!( summy("0"), 0);
}
#[test]
fn test1() {
   assert_eq!( summy("1"), 1);
}
#[test]
fn test2() {
   assert_eq!( summy("1 2"), 3);
}
#[test]
fn test3() {
   assert_eq!( summy("1 2 3"), 6);
}
#[test]
fn test4() {
   assert_eq!( summy("3 3 3"), 9);
}
#[test]
fn test5() {
   assert_eq!( summy("3 2 1"), 6);
}
#[test]
fn test6() {
   assert_eq!( summy("0 0 0 0"), 0);
}
#[test]
fn test7() {
   assert_eq!( summy("1 1 1"), 3);
}
#[test]
fn test8() {
   assert_eq!( summy("1 1 1 0"), 3);
}
#[test]
fn test9() {
   assert_eq!( summy("0 1 0"), 1);
}


fn main() {}
