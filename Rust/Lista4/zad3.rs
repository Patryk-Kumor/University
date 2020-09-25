pub fn highlight(code: &str) -> String {
  let mut res : String = String::new();
  let iterator : Vec<char> = code.chars().collect();
  if iterator.len() == 0 { return res; }
  match iterator[0] {
    'F' => res.push_str("<span style=\"color: pink\">"),
    'L' => res.push_str("<span style=\"color: red\">"),
    'R' => res.push_str("<span style=\"color: green\">"),
    '0'..='9' => res.push_str("<span style=\"color: orange\">"),
    _ => {}
  }
  res.push_str(&iterator[0].to_string());
  let mut i = 1; let mut curr = iterator[0];
  while i != iterator.len()
  {
      if (curr == iterator[i]) || ((curr >= '0' && curr <= '9') && (iterator[i] >= '0' && iterator[i] <= '9')) {
          res.push_str(&iterator[i].to_string()); i+=1;
      }
      else {
          if curr != '(' && curr != ')' { 
              res.push_str("</span>"); 
          }
          match iterator[i] {
            'F' => res.push_str("<span style=\"color: pink\">"),
            'L' => res.push_str("<span style=\"color: red\">"),
            'R' => res.push_str("<span style=\"color: green\">"),
            '0'..='9' => res.push_str("<span style=\"color: orange\">"),
            _ => {}   
          }
          curr = iterator[i];
          res.push_str(&iterator[i].to_string());
          i+=1;
      }
  }
  if curr != '(' && curr != ')' { 
      res.push_str("</span>"); 
  }
  res.to_string()
}

#[test]
fn test0() {
    assert_eq!(highlight("F"), r#"<span style="color: pink">F</span>"#);
}
#[test]
fn test1() {
    assert_eq!(highlight("R"), r#"<span style="color: green">R</span>"#);
}
#[test]
fn test2() {
    assert_eq!(highlight("L"), r#"<span style="color: red">L</span>"#);
}
#[test]
fn test3() {
    assert_eq!(highlight("FFFF"), r#"<span style="color: pink">FFFF</span>"#);
}
#[test]
fn test4() {
    assert_eq!(highlight("RRRR"), r#"<span style="color: green">RRRR</span>"#);
}
#[test]
fn test5() {
    assert_eq!(highlight("LLLL"), r#"<span style="color: red">LLLL</span>"#);
}
#[test]
fn test6() {
    assert_eq!(highlight("0"), r#"<span style="color: orange">0</span>"#);
}
#[test]
fn test7() {
    assert_eq!(highlight("0123456789"), r#"<span style="color: orange">0123456789</span>"#);
}
#[test]
fn test8() {
    assert_eq!(highlight("F3RF5LF7"), r#"<span style="color: pink">F</span><span style="color: orange">3</span><span style="color: green">R</span><span style="color: pink">F</span><span style="color: orange">5</span><span style="color: red">L</span><span style="color: pink">F</span><span style="color: orange">7</span>"#);
}
#[test]
fn test9() {
    assert_eq!(highlight("FFFR345F2LL"), r#"<span style="color: pink">FFF</span><span style="color: green">R</span><span style="color: orange">345</span><span style="color: pink">F</span><span style="color: orange">2</span><span style="color: red">LL</span>"#);
}

fn main() {
    println!("{}", highlight("F")); println!("");
    println!("{}", highlight("R")); println!("");
    println!("{}", highlight("L")); println!("");
    println!("{}", highlight("FFFF")); println!("");
    println!("{}", highlight("RRRR")); println!("");
    println!("{}", highlight("LLLL")); println!("");
    println!("{}", highlight("0")); println!("");
    println!("{}", highlight("0123456789")); println!("");

 

}
