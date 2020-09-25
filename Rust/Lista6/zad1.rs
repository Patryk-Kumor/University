fn encode(msg: String, n: i32) -> Vec<i32> {
    let map: Vec<char> = "abcdefghijklmnopqrstuvwxyz".chars().collect();
    let mut digits : Vec<i32> = vec![]; let mut n = n; 
    while n > 0 { digits.push(n % 10); n = n / 10; }
    digits.reverse();
    let mut v: Vec<i32> = Vec::new(); let mut j = 0;
    let to_convert: Vec<char> = msg.chars().collect();
    for i in 0..to_convert.len() {
          let index = map.iter().position(|&r| r == to_convert[i]);
          match index {
              Some(x) => v.push( ((x+1)as i32) + (digits[ j ]) ),
              None =>  v.push(0),
          } 
          j = (j + 1) % digits.len();
      }
    v
}

#[test]
fn test0() { assert_eq!(encode("scout".to_string(), 1939), vec![20, 12, 18, 30, 21]);
}
#[test]
fn test1() { assert_eq!(encode("helloworld".to_string(), 1), vec![9, 6, 13, 13, 16, 24, 16, 19, 13, 5]);
}
#[test]
fn test2() { assert_eq!(encode("helloworld".to_string(), 13), vec![9, 8, 13, 15, 16, 26, 16, 21, 13, 7]);
}
#[test]
fn test3() { assert_eq!(encode("helloworld".to_string(), 50), vec![13, 5, 17, 12, 20, 23, 20, 18, 17, 4]);
}
#[test]
fn test4() { assert_eq!(encode("dog".to_string(), 2), vec![6, 17, 9]);
}
#[test]
fn test5() { assert_eq!(encode("cat".to_string(), 5), vec![8, 6, 25]);
}
#[test]
fn test6() { assert_eq!(encode("rust".to_string(), 666), vec![24, 27, 25, 26]);
}
#[test]
fn test7() { assert_eq!(encode("abcd".to_string(), 1), vec![2, 3, 4, 5]);
}
#[test]
fn test8() { assert_eq!(encode("abcd".to_string(), 2), vec![3, 4, 5, 6]);
}
#[test]
fn test9() { assert_eq!(encode("masterpiece".to_string(), 1939), vec![14, 10, 22, 29, 6, 27, 19, 18, 6, 12, 8]);
}

fn main() { println!();
}
