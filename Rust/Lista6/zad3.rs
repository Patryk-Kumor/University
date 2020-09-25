fn print(n: i32) -> Option<String> {
    if n <= 0 || n % 2 == 0 { return None; }
    let mut s: String = String::new();
    let mut i = 1; let mut j = n/2 ;
    while i <= n { s.push_str( &" ".repeat(( j )as usize));
                   s.push_str( &"*".repeat(( i )as usize));
                   s.push_str( &"\n" );
                   i+=2; j-=1; }
    i-=4; j+=2;
    while i >= 1 { s.push_str( &" ".repeat(( j )as usize));
                   s.push_str( &"*".repeat(( i )as usize));
                   s.push_str( &"\n" );
                   i-=2; j+=1; }                
    return Some(s);
}

#[test]
fn test0() { assert_eq!(print(1), Some("*\n".to_string()));
}
#[test]
fn test1() { assert_eq!(print(2), None);
}
#[test]
fn test2() { assert_eq!(print(3), Some(" *\n***\n *\n".to_string()));
}
#[test]
fn test3() { assert_eq!(print(4), None);
}
#[test]
fn test4() { assert_eq!(print(5), Some("  *\n ***\n*****\n ***\n  *\n".to_string()));
}
#[test]
fn test5() { assert_eq!(print(6), None);
}
#[test]
fn test6() { assert_eq!(print(7), Some("   *\n  ***\n *****\n*******\n *****\n  ***\n   *\n".to_string()));
}
#[test]
fn test7() { assert_eq!(print(8), None);
}
#[test]
fn test8() { assert_eq!(print(9), Some("    *\n   ***\n  *****\n *******\n*********\n *******\n  *****\n   ***\n    *\n".to_string()));
}
#[test]
fn test9() { assert_eq!(print(-1), None);
}

fn main() {
    println!("{:?}", print(1));
}
