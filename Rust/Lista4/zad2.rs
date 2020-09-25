fn even_numbers(array: &Vec<i32>, number: usize) -> Vec<i32> {
    let v : Vec<i32> = array.clone().into_iter().filter(|i| i%2 == 0).collect();
    v[(v.len()-number)..v.len()].to_vec()
}

#[test]
fn test0() {
    assert_eq!(even_numbers(&vec!(1, 2, 3, 4, 5, 6, 7, 8, 9), 3), vec!(4, 6, 8));
}
#[test]
fn test1() {
    assert_eq!(even_numbers(&vec!(-22, 5, 3, 11, 26, -6, -7, -8, -9, -8, 26), 2), vec!(-8, 26));
}
#[test]
fn test2() {
    assert_eq!(even_numbers(&vec!(6, -25, 3, 7, 5, 5, 7, -3, 23), 1), vec!(6));
}
#[test]
fn test4() {
    assert_eq!(even_numbers(&vec!(1,2,3,4), 1), vec!(4));
}
#[test]
fn test5() {
    assert_eq!(even_numbers(&vec!(1,2,3,4,5,6), 2), vec!(4, 6));
}
#[test]
fn test6() {
    assert_eq!(even_numbers(&vec!(0,1,2,3,3,3,3,3,3,3,3), 1), vec!(2));
}
#[test]
fn test7() {
    assert_eq!(even_numbers(&vec!(0,1,2,3,3,3,3,3,3,3,3,2), 1), vec!(2));
}
#[test]
fn test8() {
    assert_eq!(even_numbers(&vec!(2,2,2,2,2,2), 2), vec!(2,2));
}
#[test]
fn test9() {
    assert_eq!(even_numbers(&vec!(-4, 3,3), 1), vec!(-4));
}



fn main() {
}
