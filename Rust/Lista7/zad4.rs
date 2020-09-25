fn arr(n: i32) -> (Vec<i32>, Vec<i32>) {
    let mut a: Vec<i32> = vec![];
    let mut j: Vec<i32> = vec![];
    
    a.push(1); j.push(0);

    for i in 1..n {
        j.push(i - a[j[i as usize -1] as usize]);
        a.push(i - j[a[i as usize -1] as usize]);    
    }
    
    (a,j)
}

fn john(n: i32) -> Vec<i32> {
    arr(n).1
}
fn ann(n: i32) -> Vec<i32> {
    arr(n).0
}
fn sum_john(n: i32) -> i32 {
    arr(n).1.iter().sum()
}
fn sum_ann(n: i32) -> i32 {
    arr(n).0.iter().sum()
}

#[test]
fn test0() {
    assert_eq!(john(11), vec![0, 0, 1, 2, 2, 3, 4, 4, 5, 6, 6])
}
#[test]
fn test1() {
    assert_eq!(john(19), vec![0, 0, 1, 2, 2, 3, 4, 4, 5, 6, 6, 7, 7, 8, 9, 9, 10, 11, 11])
}
#[test]
fn test2() {
    assert_eq!(john(5), vec![0, 0, 1, 2, 2])
}
#[test]
fn test3() {
    assert_eq!(ann(3), vec![1, 1, 2])
}
#[test]
fn test4() {
    assert_eq!(ann(13), vec![1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6, 7, 8])
}
#[test]
fn test5() {
    assert_eq!(ann(21), vec![1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6, 7, 8, 8, 9, 9, 10, 11, 11, 12, 13])
}
#[test]
fn test6() {
    assert_eq!(sum_john(11), 33)
}
#[test]
fn test7() {
    assert_eq!(sum_john(16), 73)
}
#[test]
fn test8() {
    assert_eq!(sum_ann(4), 6)
}
#[test]
fn test9() {
    assert_eq!(sum_ann(13), 53)
}


fn main() {
}
