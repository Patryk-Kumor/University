fn printer_error(s: &str) -> String {
   let mut a = s.replace(&['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm'][..], "").len().to_string();
   a.push_str("/"); a.push_str(&s.len().to_string()); a
}

#[test]
fn test0() {
   assert_eq!(printer_error("aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"), "3/56");
}
#[test]
fn test1() {
   assert_eq!(printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"), "6/60");
}
#[test]
fn test2() {
   assert_eq!(printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyzuuuuu"), "11/65");
}
#[test]
fn test3() {
   assert_eq!(printer_error("abcdefghijklm"), "0/13");
}
#[test]
fn test4() {
   assert_eq!(printer_error("abcdefghijklmn"), "1/14");
}

fn main() {}