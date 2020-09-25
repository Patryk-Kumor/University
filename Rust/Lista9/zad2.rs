fn dont_give_me_five(start: isize, end: isize) -> isize {  
    let mut sum = 0;
    for elem in start..=end {
        let mut digit = elem.to_string().find('5');
        match digit {
            Some(_) => {}
            _ => { sum += 1; }
        }
    }
    sum
}

#[test]
fn test0() {
    assert_eq!(dont_give_me_five(1,2), 2);
}
#[test]
fn test1() {
    assert_eq!(dont_give_me_five(1,3), 3);
}
#[test]
fn test2() {
    assert_eq!(dont_give_me_five(1,4), 4);
}
#[test]
fn test3() {
    assert_eq!(dont_give_me_five(1,5), 4);
}
#[test]
fn test4() {
    assert_eq!(dont_give_me_five(-5,5), 9);
}
#[test]
fn test5() {
    assert_eq!(dont_give_me_five(-6,6), 11);
}
#[test]
fn test6() {
    assert_eq!(dont_give_me_five(0,1), 2);
}
#[test]
fn test7() {
    assert_eq!(dont_give_me_five(-15,15), 27);
}
#[test]
fn test8() {
    assert_eq!(dont_give_me_five(0,0), 1);
}
#[test]
fn test9() {
    assert_eq!(dont_give_me_five(5,5), 0);
}


fn main() {
}
