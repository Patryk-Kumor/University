fn alphabet_position(text: &str) -> String {
    let mut s = String::new();
    for elem in text.to_lowercase().chars() {
        match elem {
            'a'..='z' => { s.push_str(&(elem as u8 - 'a' as u8 + 1).to_string()); s.push(' '); },
            _   => {}
        }
    }
    s.pop();
    s
}

#[test]
fn test0() {
    assert_eq!(alphabet_position("A"), "1")
}
#[test]
fn test1() {
    assert_eq!(alphabet_position("a"), "1")
}
#[test]
fn test2() {
    assert_eq!(alphabet_position("AA"), "1 1")
}
#[test]
fn test3() {
    assert_eq!(alphabet_position("Abcd"), "1 2 3 4")
}
#[test]
fn test4() {
    assert_eq!(alphabet_position("This is string"), "20 8 9 19 9 19 19 20 18 9 14 7")
}
#[test]
fn test5() {
    assert_eq!(alphabet_position("A string"), "1 19 20 18 9 14 7")
}
#[test]
fn test6() {
    assert_eq!(alphabet_position("That string"), "20 8 1 20 19 20 18 9 14 7")
}
#[test]
fn test7() {
    assert_eq!(alphabet_position("string"), "19 20 18 9 14 7")
}
#[test]
fn test8() {
    assert_eq!(alphabet_position("ABC abc"), "1 2 3 1 2 3")
}
#[test]
fn test9() {
    assert_eq!(alphabet_position("ABC abc AbC aBc"), "1 2 3 1 2 3 1 2 3 1 2 3")
}


fn main() {
}
