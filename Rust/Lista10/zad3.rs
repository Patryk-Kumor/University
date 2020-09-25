fn fun(balance: &str, worth_sum: Vec<i32>) -> i32 {
  let mut sum = 0;
  let mut iter = 0;
  for worth in balance.split(" ").collect::<Vec<&str>>() {
      sum += worth.parse::<i32>().unwrap() * worth_sum[iter]; 
      iter += 1;
  }
  sum
}

fn good_vs_evil(good: &str, evil: &str) -> String {
  let  good_worth: Vec<i32> = vec![1,2,3,3,4,10]; 
  let  evil_worth: Vec<i32> = vec![1,2,2,2,3,5,10]; 

  let  sum_good = fun(good, good_worth);
  let  sum_evil = fun(evil, evil_worth);

       if sum_good == sum_evil { return "Battle Result: No victor on this battle field".to_string(); } 
  else if sum_good >  sum_evil { return "Battle Result: Good triumphs over Evil".to_string(); }
  else                         { return "Battle Result: Evil eradicates all trace of Good".to_string(); }
}

#[test]
fn test0() {
    let a = "0 0 0 0 0 0";
    let b = "0 0 0 0 0 0 0";
    assert_eq!(good_vs_evil(a, b), "Battle Result: No victor on this battle field" );
}
#[test]
fn test1() {
    let a = "0 0 0 0 0 0";
    let b = "0 0 0 0 0 0 0";
    assert_eq!(good_vs_evil(a, b), "Battle Result: No victor on this battle field" );
}
#[test]
fn test2() {
    let a = "0 0 0 0 0 0";
    let b = "0 0 0 0 0 0 0";
    assert_eq!(good_vs_evil(a, b), "Battle Result: No victor on this battle field" );
}
#[test]
fn test3() {
    let a = "0 0 0 0 0 0";
    let b = "0 0 0 0 0 0 0";
    assert_eq!(good_vs_evil(a, b), "Battle Result: No victor on this battle field" );
}
#[test]
fn test4() {
    let a = "0 0 0 0 0 0";
    let b = "0 0 0 0 0 0 0";
    assert_eq!(good_vs_evil(a, b), "Battle Result: No victor on this battle field" );
}
#[test]
fn test5() {
    let a = "0 0 0 0 0 0";
    let b = "0 0 0 0 0 0 0";
    assert_eq!(good_vs_evil(a, b), "Battle Result: No victor on this battle field" );
}
#[test]
fn test6() {
    let a = "0 0 0 0 0 0";
    let b = "0 0 0 0 0 0 0";
    assert_eq!(good_vs_evil(a, b), "Battle Result: No victor on this battle field" );
}
#[test]
fn test7() {
    let a = "0 0 0 0 0 0";
    let b = "0 0 0 0 0 0 0";
    assert_eq!(good_vs_evil(a, b), "Battle Result: No victor on this battle field" );
}
#[test]
fn test8() {
    let a = "0 0 0 0 0 0";
    let b = "0 0 0 0 0 0 0";
    assert_eq!(good_vs_evil(a, b), "Battle Result: No victor on this battle field" );
}
#[test]
fn test9() {
    let a = "0 0 0 0 0 0";
    let b = "0 0 0 0 0 0 0";
    assert_eq!(good_vs_evil(a, b), "Battle Result: No victor on this battle field" );
}

fn main() {
}
