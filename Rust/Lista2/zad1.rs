fn get_count(string: &str) -> usize {
  string.chars().filter(|c| (['a', 'e', 'i', 'o', 'u']).contains(c)).count()
}

#[test]
fn test0() {
   assert_eq!(get_count("abracadabra"), 5);
}
#[test]
fn test1() {
   assert_eq!(get_count("a"), 1);
}
#[test]
fn test2() {
   assert_eq!(get_count("aeiou"), 5);
}
#[test]
fn test3() {
   assert_eq!(get_count("abe"), 2);
}
#[test]
fn test4() {
   assert_eq!(get_count("xyz"), 0);
}
#[test]
fn test5() {
   assert_eq!(get_count("xyza"), 1);
}
#[test]
fn test6() {
   assert_eq!(get_count("axayaza"), 4);
}
#[test]
fn test7() {
   assert_eq!(get_count("axeyizo"), 4);
}
#[test]
fn test8() {
   assert_eq!(get_count("aaaaa"), 5);
}
#[test]
fn test9() {
   assert_eq!(get_count("aaaaaiiiiiooooo"), 15);
}


fn main() {}
