fn next_bigger_number(n: i64) -> i64 {
    let mut num = n; 
    let mut digits : Vec<i64> = vec![];
    while num > 0 { digits.push(num % 10); num = num / 10; }
    digits.reverse();
    
    let mut i = digits.len() - 1;
    while (i > 0) && !(digits[i] > digits[i-1]) { i -= 1; }
    
    if i == 0 { return -1 }
    
    let it = digits[i-1]; let mut smallest = i;
    for j in i+1..digits.len() {
        if digits[j] > it && digits[j] < digits[smallest] { smallest = j; }
    }
    
    digits[smallest] ^= digits[i-1]; 
    digits[i-1] ^= digits[smallest]; 
    digits[smallest] ^= digits[i-1];
    
    let mut a = digits.clone(); let mut b: Vec<i64> = vec![];
    for i in 0..(digits.len()-i) {b.push(a[digits.len()-i-1]); a.pop();} b.sort();
    a.extend(b);
    
    num = 0;
    for elem in 0..a.len() { num = num*10 + a[elem]}
    num
}

#[test]
fn test0() { assert_eq!(21, next_bigger_number(12)); }
#[test]
fn test1() { assert_eq!(531, next_bigger_number(513)); }
#[test]
fn test2() { assert_eq!(2071, next_bigger_number(2017)); }
#[test]
fn test3() { assert_eq!(441, next_bigger_number(414)); }
#[test]
fn test4() { assert_eq!(414, next_bigger_number(144)); }
#[test]
fn test5() { assert_eq!(-1, next_bigger_number(11)); }
#[test]
fn test6() { assert_eq!(-1, next_bigger_number(321)); }
#[test]
fn test7() { assert_eq!(-1, next_bigger_number(1)); }
#[test]
fn test8() { assert_eq!(132, next_bigger_number(123)); }
#[test]
fn test9() { assert_eq!(1243, next_bigger_number(1234)); }

fn main() {}