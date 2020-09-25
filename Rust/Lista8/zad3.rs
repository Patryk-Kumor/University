fn fac(n: u64) -> u64 {
    let mut num = 1;
    let mut i = 1;
    
    while i <= n {
        num = num * i;
        i+=1;
    }
    num
}

fn dec2_fact_string(nb: u64) -> String {    
    let mut n = nb;
    let mut i = 1;
    let mut tab : Vec<String> = vec![];
    while n > 0 {
        let mut num = n % i; 
        if num < 10 { tab.push( num.to_string() ); }
        else { tab.push( ((num as u8 + 55 as u8) as char).to_string() ); }
        n = n / i;        
        i += 1;
    }
    tab.reverse();
    tab.into_iter().map(|i| i.to_string()).collect::<String>() 
}

fn fact_string_2dec(s: String) -> u64 {
    let mut s: Vec<char> = s.chars().collect(); s.reverse();
    let mut sum = 0;
    let mut i: u64 = 0;
    for elem in s {
        if  (elem as u64 - '0' as u64) < 10 {
            sum += (elem as u64 - '0' as u64) * (fac(i));
        }
        else {
            sum += (elem as u64 - 'A' as u64 + 10) * (fac(i));            
        }
        i+=1;
}

#[test]
fn test0() {
    assert_eq!(dec2_fact_string(1), "1")
}

#[test]
fn test1() {
    assert_eq!(dec2_fact_string(123), "1")
}

#[test]
fn test2() {
    assert_eq!(dec2_fact_string(120), "1")
}

#[test]
fn test3() {
    assert_eq!(dec2_fact_string(363), "1")
}

#[test]
fn test4() {
    assert_eq!(dec2_fact_string(555), "1")
}

#[test]
fn test5() {
    assert_eq!(dec2_fact_string(30000), "1")
}

#[test]
fn test6() {
    assert_eq!(dec2_fact_string("A"), "1")
}

#[test]
fn test7() {
    assert_eq!(dec2_fact_string("A"), "1")
}

#[test]
fn test8() {
    assert_eq!(dec2_fact_string("A"), "1")
}
#[test]
fn test9() {
    assert_eq!(dec2_fact_string("A"), "1")
}
fn main() {
}
