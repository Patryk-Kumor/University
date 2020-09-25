fn last_digit(lst: &[u64]) -> u64 {
    if lst.len() == 0 { return 1; }
    let mut n: u128 = 1;
    for i in (0..lst.len()).rev() {
        if n < 4 {
            n = ((lst[i] % 1000) as u128).pow(n as u32);
        }
        else {
            n = ((lst[i] % 1000) as u128).pow((n % 4 + 4) as u32);
        }
    }
    (n % 10) as u64
}

#[test]
fn test0() {
    assert_eq!(last_digit(&vec![]), 1);
}
#[test]
fn test1() {
    assert_eq!(last_digit(&vec![0, 0]), 1);
}
#[test]
fn test2() {
    assert_eq!(last_digit(&vec![0, 0, 0]), 0);
}
#[test]
fn test3() {
    assert_eq!(last_digit(&vec![1, 2]), 1);
}
#[test]
fn test4() {
    assert_eq!(last_digit(&vec![3, 4, 5]), 1);
}
#[test]
fn test5() {
    assert_eq!(last_digit(&vec![1,2,3,4,5]), 1);
}
#[test]
fn test6() {
    assert_eq!(last_digit(&vec![1,2,3,4,5,6,7,8,9,0]), 1);
}
#[test]
fn test7() {
    assert_eq!(last_digit(&vec![937640, 767456, 981242]), 0);
}
#[test]
fn test8() {
    assert_eq!(last_digit(&vec![123232, 694022, 140249]), 6);
}
#[test]
fn test9() {
    assert_eq!(last_digit(&vec![499942, 898102, 846073]), 6);
}


fn main() {
}
