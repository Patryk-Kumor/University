struct Cipher {
  a: Vec<char>,
  b: Vec<char>,
}

impl Cipher {
  fn new(map1: &str, map2: &str) -> Cipher {
    Cipher{
        a: map1.chars().collect(),
        b: map2.chars().collect(),
    }
  }
  
  fn encode(&self, string: &str) -> String {
      let mut to_convert: Vec<char> = string.chars().collect();
      for i in 0..to_convert.len() {
          let index = self.a.iter().position(|&r| r == to_convert[i]);
          match index {
              Some(x) => to_convert[i] = self.b[x],
              None =>  to_convert[i] =  to_convert[i],
          } 
      }
      to_convert.into_iter().collect()  
  }
  
  fn decode(&self, string: &str) -> String {
      let mut to_convert: Vec<char> = string.chars().collect();
      for i in 0..to_convert.len() {
          let index = self.b.iter().position(|&r| r == to_convert[i]);
          match index {
              Some(x) => to_convert[i] = self.a[x],
              None =>  to_convert[i] =  to_convert[i],
          } 
      }
      to_convert.into_iter().collect()  
  }
}

#[test]
fn test0() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";
  let cipher = Cipher::new(map1, map2);   
  assert_eq!(cipher.encode("abc"), "eta"); }
#[test]
fn test1() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";
  let cipher = Cipher::new(map1, map2);   
  assert_eq!(cipher.encode("xyz"), "qxz"); }
#[test]
fn test2() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";
  let cipher = Cipher::new(map1, map2);   
  assert_eq!(cipher.decode("eirfg"), "aeiou"); }
#[test]
fn test3() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";
  let cipher = Cipher::new(map1, map2);   
  assert_eq!(cipher.decode("erlang"), "aikcfu"); }
#[test]
fn test4() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";
  let cipher = Cipher::new(map1, map2);   
  assert_eq!(cipher.encode("az"), "ez"); }
#[test]
fn test5() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "abcdefghijklmnopqrstuvwxyz";
  let cipher = Cipher::new(map1, map2);   
  assert_eq!(cipher.decode("abcdefghijklmnopqrstuvwxyz"), "abcdefghijklmnopqrstuvwxyz"); }
#[test]
fn test6() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "abcdefghijklmnopqrstuvwxyz";
  let cipher = Cipher::new(map1, map2);   
  assert_eq!(cipher.decode("a"), "a"); }
#[test]
fn test7() {
  let map1 = "abc";
  let map2 = "abc";
  let cipher = Cipher::new(map1, map2);   
  assert_eq!(cipher.decode("abc"), "abc"); }
#[test]
fn test8() {
  let map1 = "a";
  let map2 = "a";
  let cipher = Cipher::new(map1, map2);   
  assert_eq!(cipher.decode("a"), "a"); }
#[test]
fn test9() {
  let map1 = "a";
  let map2 = "a";
  let cipher = Cipher::new(map1, map2);   
  assert_eq!(cipher.decode("z"), "z"); }


fn main() {
}
