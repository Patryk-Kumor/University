fn longest(a1: &str, a2: &str) -> String {
    let mut chars: Vec<char> = a1.to_string().chars().collect();
    let chars2: Vec<char> = a2.to_string().chars().collect();

    chars.extend(chars2); chars.sort(); chars.dedup(); 
    
    chars.into_iter().collect()
}

#[test]
fn test0() {
   assert_eq!( longest("aretheyhere", "yestheyarehere"), "aehrsty");
}
#[test]
fn test1() {
   assert_eq!( longest("loopingisfunbutdangerous", "lessdangerousthancoding"), "abcdefghilnoprstu");
}
#[test]
fn test2() {
   assert_eq!( longest("abc", "def"), "abcdef");
}
#[test]
fn test3() {
   assert_eq!( longest("aabbcc", "ddeeff"), "abcdef");
}
#[test]
fn test4() {
   assert_eq!( longest("cba", "fed"), "abcdef");
}
#[test]
fn test5() {
   assert_eq!( longest("aeaaaaaaeaaaaaabeebbeebbbebebebbbbebcddddeddedddedddd", "f"), "abcdef");
}
#[test]
fn test6() {
   assert_eq!( longest("a", "b"), "ab");
}
#[test]
fn test7() {
   assert_eq!( longest("bbbbbbbbbbb", "aaaaaaaaaaaaaaaaaa"), "ab");
}
#[test]
fn test8() {
   assert_eq!( longest("ababa", "ababa"), "ab");
}
#[test]
fn test9() {
   assert_eq!( longest("abc", ""), "abc");
}


fn main() {}
