use std::collections::HashMap;

struct MorseDecoder {
     morse_code: HashMap<String, String>,
}

impl MorseDecoder {
    fn new() -> MorseDecoder {
        MorseDecoder{ morse_code :
        [("....-", "4"),("--..--", ","),(".--", "W"),(".-.-.-", "."),("..---", "2"),(".", "E"),("--..", "Z"),(".----", "1"),(".-..", "L"),
        (".--.", "P"),(".-.", "R"),("...", "S"),("-.--", "Y"),("...--", "3"),(".....", "5"),("--.", "G"),("-.--.", "("),("-....", "6"),
        (".-.-.", "+"),("...-..-", "$"),(".--.-.", "@"),("...---...", "SOS"),("..--.-", "_"),("-.", "N"),("-..-", "X"),("-----", "0"),
        ("....", "H"),("-...", "B"),(".---", "J"),("---...", ","),("-", "T"),("---..", "8"),("-..-.", "/"),("--.-", "Q"),("...-", "V"),
        ("----.", "9"),("--", "M"),("-.-.-.", ";"),("-.-.--", "!"),("..-.", "F"),("..--..", "?"),("-...-", "="),("..-", "U"),(".----.", "'"),
        ("---", "O"),("-.--.-", ")"),("..", "I"),("-....-", "-"),(".-..-.", "\""),(".-", "A"),("-.-.", "C"),("-..", "D"),(".-...", "&"),
        ("--...", "7"),("-.-", "K")].iter().map(|(k, v)| (k.to_string(), v.to_string())).collect()}
    }

    pub fn decode_bits(&self, encoded: &str) -> String {
        let mut x: Vec<&str> = encoded.trim_matches('0').split("0").collect(); 
        x.extend( encoded.trim_matches('0').split("1").collect::<Vec<&str>>());
        x.sort(); 
        x.dedup(); 
        if x[0] == "" { x.remove(0); }
        
        let mut z: Vec<usize> = x.clone().into_iter().map({|e| e.len()}).collect();
        z.sort();
        let unit = z[0];
        
        let r = encoded
                .trim_matches('0')
                .replace(&"0".repeat(7*unit), "   ")
                .replace(&"0".repeat(3*unit), " ")
                .replace(&"1".repeat(3*unit), "-")
                .replace(&"0".repeat(unit), "")
                .replace(&"1".repeat(unit), ".");
        r.to_string()   
    }
    pub fn decode_morse(&self, encoded: &str) -> String {
        let mut ret: String = String::new();
        let words: Vec<&str> = encoded.trim().split("   ").collect();   
        if words == vec![""] { return ret; }
        for word in words {
            let signs = word.split(" ");
            let mut word_string = String::new();
            for sign in signs {
                word_string.push_str( &self.morse_code[sign].clone() );
            }
            ret.push_str( & word_string );
            ret.push(' ');
        }
        ret.pop();
        ret.to_string()
    } 
}

#[test]
fn test0() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("1")), "E".to_string());
}
#[test]
fn test1() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("11")), "E".to_string());
}
#[test]
fn test2() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("111")), "E".to_string());
}
#[test]
fn test3() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("1111111111111111")), "E".to_string());
}
#[test]
fn test4() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("101")), "I".to_string());
}
#[test]
fn test5() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("10101")), "S".to_string());
}
#[test]
fn test6() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("10101011101110111010101")), "SOS".to_string());
}
#[test]
fn test7() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("000000000000000000000000000000001")), "E".to_string());
}
#[test]
fn test8() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("1000000000000000000000000000")), "E".to_string());
}
#[test]
fn test9() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("0000000000000010000000000000000000000000")), "E".to_string());
}

fn main() {
}
