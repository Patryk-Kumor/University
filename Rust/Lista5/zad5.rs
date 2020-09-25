fn dbl_linear(n: u32) -> u32{
    let mut v = vec![]; v.push(1);
    let mut i = 0 as usize;
    let mut a = 0 as usize; let mut anext = 0;
    let mut b = 0 as usize; let mut bnext = 0;
    while i < (n as usize) {
        anext  = 2 * (v[a] as u32) + 1;
        bnext  = 3 * (v[b] as u32) + 1;
        if anext <= bnext {
            v.push(anext); a+=1;
            if anext == bnext { b+=1; }
        }
        else{
            v.push(bnext);
            b+=1;
        }
        i+=1; 
    }
    v[n as usize]
}

#[test]
fn test0() { assert_eq!(dbl_linear(1), 3); }
#[test]
fn test1() { assert_eq!(dbl_linear(2), 4); }
#[test]
fn test2() { assert_eq!(dbl_linear(3), 7); }
#[test]
fn test3() { assert_eq!(dbl_linear(4), 9); }
#[test]
fn test4() { assert_eq!(dbl_linear(5), 10); }
#[test]
fn test5() { assert_eq!(dbl_linear(6), 13); }
#[test]
fn test6() { assert_eq!(dbl_linear(7), 15); }
#[test]
fn test7() { assert_eq!(dbl_linear(8), 19); }
#[test]
fn test8() { assert_eq!(dbl_linear(9), 21); }
#[test]
fn test9() { assert_eq!(dbl_linear(10), 22); }

fn main() {

}
