use std::collections::BTreeMap;

fn sum_pairs(ints: &[i8], s: i8) -> Option<(i8, i8)> {
    let mut seen = BTreeMap::new();
    for i in 0..ints.len() {
        if seen.contains_key(&( s - ints[i] )) { return  Some((s - ints[i], ints[i])); }
        else { seen.insert( ints[i], true ); };
    }
    return None
}

#[test]
fn test0() {
    assert_eq!(sum_pairs(&[1, 4, 8, 7, 3, 15], 8), Some((1, 7)));
}
#[test]
fn test1() {
    assert_eq!(sum_pairs(&[1, -2, 3, 0, -6, 1], -6), Some((0, -6)));
}
#[test]
fn test2() {
    assert_eq!(sum_pairs(&[20, -13, 40], -7), None);
}
#[test]
fn test3() {
    assert_eq!(sum_pairs(&[1, 2, 3, 4, 1, 0], 2), Some((1, 1)));
}
#[test]
fn test4() {
    assert_eq!(sum_pairs(&[10, 5, 2, 3, 7, 5], 10), Some((3, 7)));
}
#[test]
fn test5() {
    assert_eq!(sum_pairs(&[4, -2, 3, 3, 4], 8), Some((4, 4)));
}
#[test]
fn test6() {
    assert_eq!(sum_pairs(&[0, 2, 0], 0), Some((0, 0)));
}
#[test]
fn test7() {
    assert_eq!(sum_pairs(&[5, 9, 13, -3], 10), Some((13, -3)));
}
#[test]
fn test8() {
    assert_eq!(sum_pairs(&[0,0,0,0,0,0,0], 0), Some((0, 0)));
}
#[test]
fn test9() {
    assert_eq!(sum_pairs(&[0,0,0,0,0,0,0], 1), None);
}
fn main() {
}
