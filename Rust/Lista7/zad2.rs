use std::collections::BTreeMap;

fn letter_frequency(input: &str) -> BTreeMap<char, i32> {
    let mut dic = BTreeMap::new();
    let s: Vec<char> = input.to_string().to_lowercase().chars().collect();
    for elem in s {
        if (elem >= 'A' as char && elem <= 'Z' as char) || (elem >= 'a' as char && elem <= 'z' as char) {
            *dic.entry(elem).or_insert(0) += 1;
        }
    }
    dic
}

#[test]
fn test0() {
    let answer: BTreeMap<char, i32> = [('a', 1)]
                                      .iter().cloned().collect();
    assert_eq!(letter_frequency("a"), answer);
}
#[test]
fn test1() {
    let answer: BTreeMap<char, i32> = [('a', 1)]
                                      .iter().cloned().collect();
    assert_eq!(letter_frequency("A"), answer);
}
#[test]
fn test2() {
    let answer: BTreeMap<char, i32> = [('a', 3)]
                                      .iter().cloned().collect();
    assert_eq!(letter_frequency("aaa"), answer);
}
#[test]
fn test3() {
    let answer: BTreeMap<char, i32> = [('a', 3)]
                                      .iter().cloned().collect();
    assert_eq!(letter_frequency("AAA"), answer);
}
#[test]
fn test4() {
    let answer: BTreeMap<char, i32> = [('a', 6)]
                                      .iter().cloned().collect();
    assert_eq!(letter_frequency("AaAaAa"), answer);
}
#[test]
fn test5() {
    let answer: BTreeMap<char, i32> = [('a', 1), ('b', 1), ('c', 1)]
                                      .iter().cloned().collect();
    assert_eq!(letter_frequency("abc"), answer);
}
#[test]
fn test6() {
    let answer: BTreeMap<char, i32> = [('a', 1), ('b', 1), ('c', 1)]
                                      .iter().cloned().collect();
    assert_eq!(letter_frequency("aBc"), answer);
}
#[test]
fn test7() {
    let answer: BTreeMap<char, i32> = [('a', 2), ('b', 2), ('c', 2)]
                                      .iter().cloned().collect();
    assert_eq!(letter_frequency("AaBbCc"), answer);
}
#[test]
fn test8() {
    let answer: BTreeMap<char, i32> = [('a', 2), ('b', 2), ('c', 2)]
                                      .iter().cloned().collect();
    assert_eq!(letter_frequency("Aa Bb Cc"), answer);
}
#[test]
fn test9() {
    let answer: BTreeMap<char, i32> = [('a', 2), ('b', 2), ('c', 2), ('x', 9)]
                                      .iter().cloned().collect();
    assert_eq!(letter_frequency("xAxax xBxbx xCxcx"), answer);
}

fn main() {
}
