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

    fn decode_morse(&self, encoded: &str) -> String {
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
    assert_eq!(decoder.decode_morse(".... . -.--"), "HEY");
}
#[test]
fn test1() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse("           .... . -.--       "), "HEY");
}
#[test]
fn test2() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse("                       .... . -.--"), "HEY");
}
#[test]
fn test3() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(".... . -.--                    "), "HEY");
}
#[test]
fn test4() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(".... . -.--   .--- ..- -.. ."), "HEY JUDE");
}
#[test]
fn test5() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse("     .... . -.--   .--- ..- -.. ."), "HEY JUDE");
}
#[test]
fn test6() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(".... . -.-- .... . -.--"), "HEYHEY");
}
#[test]
fn test7() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse("... --- ..."), "SOS");
}
#[test]
fn test8() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse("  ...---...   "), "SOS");
}
#[test]
fn test9() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse("...---..."), "SOS");
}

fn main() {
}
