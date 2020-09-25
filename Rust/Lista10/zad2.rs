use std::collections::BTreeMap;

fn stock_list(list_art: Vec<&str>, list_cat: Vec<&str>) -> String {
    let mut dic: BTreeMap<char, i32> = BTreeMap::new();
    let mut ret: Vec<String> = vec![];
    
    for elem in list_art {
        let temp: Vec<&str> = elem.split(" ").collect();
        *dic.entry(temp[0].chars().next().unwrap()).or_insert(0) += temp[1].parse::<i32>().unwrap();
    } 
    
    if dic.is_empty() { return String::new() }
    
    for elem in list_cat {
        let ch = &elem.chars().next().unwrap();
        ret.push( format!("({} : {})", ch, *dic.get(ch).unwrap_or(&0)) );
    }
    
    ret.into_iter().collect::<Vec<String>>().join(" - ")
}

#[test]
fn test0() {
    let a = vec!["BBAR 150", "CDXE 515", "BKWR 250", "BTSQ 890", "DRTY 600"];
    let b = vec!["A"] ;
    assert_eq!( stock_list(a,b), "(A : 0)" );
}
#[test]
fn test1() {
    let a = vec!["BBAR 150", "CDXE 515", "BKWR 250", "BTSQ 890", "DRTY 600"];
    let b = vec!["A", "B"] ;
    assert_eq!( stock_list(a,b), "(A : 0) - (B : 1290)" );
}
#[test]
fn test2() {
    let a = vec!["BBAR 150", "CDXE 515", "BKWR 250", "BTSQ 890", "DRTY 600"];
    let b = vec!["A", "B", "C"] ;
    assert_eq!( stock_list(a,b), "(A : 0) - (B : 1290) - (C : 515)" );
}
#[test]
fn test3() {
    let a = vec!["BBAR 150", "CDXE 515", "BKWR 250", "BTSQ 890", "DRTY 600"];
    let b = vec!["A", "B", "C", "D"] ;
    assert_eq!( stock_list(a,b), "(A : 0) - (B : 1290) - (C : 515) - (D : 600)" );
}
#[test]
fn test4() {
    let a = vec!["BBAR 50", "CDXE 50", "BKWR 50", "BTSQ 50", "DRTY 50"];
    let b = vec!["A", "B", "C", "D"] ;
    assert_eq!( stock_list(a,b), "(A : 0) - (B : 150) - (C : 50) - (D : 50)" );
}
#[test]
fn test5() {
    let a = vec!["AZB 650", "AXE 545", "AXZ 250", "AXEA 190", "AXI 800"];
    let b = vec!["A", "B", "C", "D"] ;
    assert_eq!( stock_list(a,b), "(A : 2435) - (B : 0) - (C : 0) - (D : 0)" );
}
#[test]
fn test6() {
    let a = vec!["ABAR 150", "ADXE 515", "AKWR 250", "ATSQ 890", "ARTY 600"];
    let b = vec!["A", "B", "C", "D"] ;
    assert_eq!( stock_list(a,b), "(A : 2405) - (B : 0) - (C : 0) - (D : 0)" );
}
#[test]
fn test7() {
    let a = vec!["ABAR 1500", "CDXE 5150", "BKWR 2500", "BTSQ 8900", "DRTY 6000"];
    let b = vec!["A", "B", "C", "D"] ;
    assert_eq!( stock_list(a,b), "(A : 1500) - (B : 11400) - (C : 5150) - (D : 6000)" );
}
#[test]
fn test8() {
    let a = vec![];
    let b = vec!["A", "B", "C", "D"] ;
    assert_eq!( stock_list(a,b), "" );
}
#[test]
fn test9() {
    let a = vec![];
    let b = vec!["A"] ;
    assert_eq!( stock_list(a,b), "" );
}

fn main() {
}
