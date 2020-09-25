mod solution {
    pub fn range_extraction(a: &[i32]) -> String {
        let mut s = String::new();
        let mut i = 0; let mut i_before = 0; let mut j = 0;
        while i < a.len() {
            s.push_str(&a[i].to_string());
            j = i + 1; i_before = i;
            if j < a.len() && a[i] == a[j]-1 {
                while j < a.len() && a[i] == a[j]-1 {
                    j += 1; i += 1;
                }
                if i_before + 1 == i {
                    s.push(','); s.push_str(&a[i].to_string()); 
                }
                else {
                    s.push('-'); s.push_str(&a[i].to_string()); 
                }
                if j < a.len() { s.push(','); }
            }
            else { if j < a.len() { s.push(','); } }
            i = j;
        }
        s
    }
}

#[test]
fn test0() {
    assert_eq!("0-10", solution::range_extraction(&[0,1,2,3,4,5,6,7,8,9,10]));	
}
#[test]
fn test1() {
    assert_eq!("-6,-3-1", solution::range_extraction(&[-6,-3,-2,-1,0,1]));	
}
#[test]
fn test2() {
    assert_eq!("-6", solution::range_extraction(&[-6]));	
}
#[test]
fn test3() {
    assert_eq!("-3-1", solution::range_extraction(&[-3,-2,-1,0,1]));	
}
#[test]
fn test4() {
    assert_eq!("3-5", solution::range_extraction(&[3,4,5]));	
}
#[test]
fn test5() {
    assert_eq!("14,15,17-20", solution::range_extraction(&[14,15,17,18,19,20]));	
}
#[test]
fn test6() {
    assert_eq!("15,17-20", solution::range_extraction(&[15,17,18,19,20]));	
}
#[test]
fn test7() {
    assert_eq!("17-20", solution::range_extraction(&[17,18,19,20]));	
}
#[test]
fn test8() {
    assert_eq!("0", solution::range_extraction(&[0]));	
}
#[test]
fn test9() {
    assert_eq!("0-10", solution::range_extraction(&[0,1,2,3,4,5,6,7,8,9,10]));	
}

fn main() {
    println!("Hello, world!");
}
