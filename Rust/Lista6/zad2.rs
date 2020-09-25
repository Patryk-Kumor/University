fn dig_pow(n: i64, p: i32) -> i64 {
    let mut digits : Vec<i64> = vec![]; let mut num = n;
    while num > 0 { digits.push(num % (10 as i64)); num = num / 10; }
    digits.reverse();
    let mut sum: i64 = 0; 
    let mut start: u32 = p as u32;
    for elem in digits{
        sum += elem.pow(start);
        start += 1;
    }
    if n == 0 { return -1; }
    if sum % n == 0 { return sum / n; }
    else { return -1; }
}


#[test]
fn test0() { assert_eq!(dig_pow(123, 1), -1);
}
#[test]
fn test1() { assert_eq!(dig_pow(1231, 2), -1);
}
#[test]
fn test2() { assert_eq!(dig_pow(11223, 1), -1);
}
#[test]
fn test3() { assert_eq!(dig_pow(142323, 2), -1);
}
#[test]
fn test4() { assert_eq!(dig_pow(121223, 1), -1);
}
#[test]
fn test5() { assert_eq!(dig_pow(11111, 2), -1);
}
#[test]
fn test6() { assert_eq!(dig_pow(89, 1), 1);
}
#[test]
fn test7() { assert_eq!(dig_pow(1, 1), 1);
}
#[test]
fn test8() { assert_eq!(dig_pow(0, 1), -1);
}
#[test]
fn test9() { assert_eq!(dig_pow(2, 1), 1);
}

fn main() {
    println!("{}", dig_pow(1, 2));
}
