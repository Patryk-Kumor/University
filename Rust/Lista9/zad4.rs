fn camel_case(str: &str) -> String {
    let x : Vec<&str> = str.trim().split(" ").collect();
    let mut ret : String = String::new();

    if str == "" { return ret; }

    for elem in x.clone() {
        let word: Vec<char> = elem.chars().collect();
        ret.push(word[0].to_ascii_uppercase());
        
        let mut other = elem.to_string(); other.remove(0);
        ret.push_str(&other);
    }
    ret
}

#[test]
fn test0() {
    assert_eq!(camel_case(""), "");	
}
#[test]
fn test1() {
    assert_eq!(camel_case("a"), "A");	
}
#[test]
fn test2() {
    assert_eq!(camel_case("A"), "A");	
}
#[test]
fn test3() {
    assert_eq!(camel_case("A a"), "AA");	
}
#[test]
fn test4() {
    assert_eq!(camel_case("a A"), "AA");	
}
#[test]
fn test5() {
    assert_eq!(camel_case("a a"), "AA");	
}
#[test]
fn test6() {
    assert_eq!(camel_case("a a a"), "AAA");	
}
#[test]
fn test7() {
    assert_eq!(camel_case("a b c"), "ABC");	
}
#[test]
fn test8() {
    assert_eq!(camel_case("aaa bbb ccc"), "AaaBbbCcc");	
}
#[test]
fn test9() {
    assert_eq!(camel_case("AaaBbbCcc AaaBbbCcc"), "AaaBbbCccAaaBbbCcc");	
}

fn main() {
}
