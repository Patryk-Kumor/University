extern crate regex;

use regex::Regex;

fn change(s: &str, prog: &str, version: &str) -> String {
    let mut data: Vec<String> = s.split("\n").into_iter().map({ |e| e.to_string() }).collect();
    
    data[0] = format!("Program: {}", prog);
    data[1] = format!("Author: g964");
    data[4] = format!("Date: 2019-01-01");
    
    let re = Regex::new(r"^Phone: \+1-\d{3}-\d{3}-\d{4}$").unwrap();
    if !re.is_match(&data[3]) { return "ERROR: VERSION or PHONE".to_string(); }
    data[3] = format!("Phone: +1-503-555-0090");
    
    let re = Regex::new(r"^Version: \d+\.\d+$").unwrap();
    if !re.is_match(&data[5]) { return "ERROR: VERSION or PHONE".to_string(); }
    if data[5] != "Version: 2.0" {
        data[5] = format!("Version: {}", version);
    }

    data.remove(2);  
    data.remove(5);
    
    data.into_iter().collect::<Vec<String>>().join(" ")
}

#[test]
fn test0() {
    assert_eq!( change("Program title: Primes\nAuthor: Kern\nCorporation: Gold\nPhone: +1-503-555-0091\nDate: Tues April 9, 2005\nVersion: 2.7\nLevel: Alpha",
                      "Circular", "1.5"),
                "Program: Circular Author: g964 Phone: +1-503-555-0090 Date: 2019-01-01 Version: 1.5"
    );
}
#[test]
fn test1() {
    assert_eq!( change("Program title: Factorial\nAuthor: Kern\nCorporation: Gold\nPhone: +1-503-555-0091\nDate: Tues April 9, 2005\nVersion: 6.7\nLevel: Alpha",
                      "Hammer", "1.50"),
                "Program: Hammer Author: g964 Phone: +1-503-555-0090 Date: 2019-01-01 Version: 1.50"
    );
}
#[test]
fn test2() {
    assert_eq!( change("Program title: X\nAuthor: Joseph\nCorporation: Gold\nPhone: +1-503-555-0091\nDate: Tues April 9, 2005\nVersion: 6.7\nLevel: Alpha",
                      "Circular", "1.500"),
                "Program: Circular Author: g964 Phone: +1-503-555-0090 Date: 2019-01-01 Version: 1.500"
    );
}
#[test]
fn test3() {
    assert_eq!( change("Program title: Divider\nAuthor: Kern\nCorporation: Gold\nPhone: +1-503-55555-0091\nDate: Tues April 9, 2005\nVersion: 6.7\nLevel: Alpha",
                      "Circular", "2.0"),
                "ERROR: VERSION or PHONE"
    );
}
#[test]
fn test4() {
    assert_eq!( change("Program title: Tests\nAuthor: Kern\nCorporation: Gold\nPhone: +1-503-555-0091\nDate: Tues April 9, 2005\nVersion: 1.7\nLevel: Alpha",
                      "Circular", "2.5"),
                "Program: Circular Author: g964 Phone: +1-503-555-0090 Date: 2019-01-01 Version: 2.5"
    );
}
#[test]
fn test5() {
    assert_eq!( change("Program title: Factor\nAuthor: Kern\nCorporation: Gold\nPhone: +1-503-555-0091\nDate: Tues April 9, 2005\nVersion: 2.0\nLevel: Alpha",
                      "Circular", "1.999"),
                "Program: Circular Author: g964 Phone: +1-503-555-0090 Date: 2019-01-01 Version: 2.0"
    );
}
#[test]
fn test6() {
    assert_eq!( change("Program title: Multi\nAuthor: Kern\nCorporation: Gold\nPhone: +1-503-555-0090\nDate: Tues April 9, 2005\nVersion: 2.0\nLevel: Alpha",
                      "Circular", "1.5"),
                "Program: Circular Author: g964 Phone: +1-503-555-0090 Date: 2019-01-01 Version: 2.0"
    );
}
#[test]
fn test7() {
    assert_eq!( change("Program title: TestingCase\nAuthor: Kern\nCorporation: Gold\nPhone: +1-5013-555-0091\nDate: Tues April 9, 2005\nVersion: 6.7\nLevel: Alpha",
                      "Circular", "1.5.0"),
                "ERROR: VERSION or PHONE"
    );
}
#[test]
fn test8() {
    assert_eq!( change("Program title: Numbers\nAuthor: Kern\nCorporation: Gold\nPhone: +1-503-51155-0091\nDate: Tues April 9, 2005\nVersion: 6.7\nLevel: Alpha",
                      "Circular", ".5"),
                "ERROR: VERSION or PHONE"
    );
}
#[test]
fn test9() {
    assert_eq!( change("Program title: First\nAuthor: Kern\nCorporation: Gold\nPhone: +1-503-555-000091\nDate: Tues April 9, 2005\nVersion: 6.7\nLevel: Alpha",
                      "Hammer", "11.5"),
                "ERROR: VERSION or PHONE"
    );
}

fn main() {

}
