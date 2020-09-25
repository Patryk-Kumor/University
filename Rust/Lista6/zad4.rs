fn comp(a: Vec<i64>, b: Vec<i64>) -> bool {
    let mut tab_a = a;
    let mut tab_b = b;
 
    //if tab_b.len() != tab_a.len() { return false }
    
    for i in 0..tab_a.len() {
        tab_a[i] = tab_a[i]*tab_a[i];
    }
    
    tab_a.sort(); tab_b.sort();
    
    tab_a == tab_b
}

#[test]
fn test0() { assert_eq!(comp(vec![], vec![]), true);
}
#[test]
fn test1() { assert_eq!(comp(vec![1], vec![1]), true);
}
#[test]
fn test2() { assert_eq!(comp(vec![1,1], vec![1,1]), true);
}
#[test]
fn test3() { assert_eq!(comp(vec![1,1,1], vec![1,1,1]), true);
}
#[test]
fn test4() { assert_eq!(comp(vec![2], vec![4]), true);
}
#[test]
fn test5() { assert_eq!(comp(vec![2,2,2], vec![4,4,4]), true);
}
#[test]
fn test6() { assert_eq!(comp(vec![1,2,3], vec![1,4,9]), true);
}
#[test]
fn test7() { assert_eq!(comp(vec![1,2,3], vec![9,4,1]), true);
}
#[test]
fn test8() { assert_eq!(comp(vec![3,2,1], vec![4,1,9]), true);
}
#[test]
fn test9() { assert_eq!(comp(vec![0], vec![0]), true);
}



fn main() {
    println!("Hello, world!");
}
