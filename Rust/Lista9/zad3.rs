fn order(sentence: &str) -> String {
    if sentence == String::new() {return String::new();}
    
    let mut ret: String = String::new();
    let mut it: Vec<(char, &str)> = vec![];
    
    for word in sentence.split(" ").collect::<Vec<&str>>() {
        let x: Vec<char> = word.chars().into_iter().filter({|e| e.is_ascii_digit()}).collect();
        it.push((x[0], word));
    }
    it.sort();
    for elem in it.clone() {
        ret.push_str(elem.1); ret.push(' ');
    }
    ret.pop();
    ret
}

#[test]
fn test0() {
    assert_eq!(order(""), "");
}
#[test]
fn test1() {
    assert_eq!(order("is2 Thi1s T4est 3a"), "Thi1s is2 3a T4est");
}
#[test]
fn test2() {
    assert_eq!(order("A1 B2 C2"), "A1 B2 C2");
}
#[test]
fn test3() {
    assert_eq!(order("ABC2 ABC1"), "ABC1 ABC2");
}
#[test]
fn test4() {
    assert_eq!(order("A3 B1 C2"), "B1 C2 A3");
}
#[test]
fn test5() {
    assert_eq!(order("A1 a2 A3"), "A1 a2 A3");
}
#[test]
fn test6() {
    assert_eq!(order("a1 A2"), "a1 A2");
}
#[test]
fn test7() {
    assert_eq!(order("A1"), "A1");
}
#[test]
fn test8() {
    assert_eq!(order("A9"), "A9");
}
#[test]
fn test9() {
    assert_eq!(order("is3 Thi2s T1est 4a"), "T1est Thi2s is3 4a");
}

fn main() {
}
