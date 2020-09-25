pub fn extend_up(mut res: Vec<Vec<char>>, width: usize) -> Vec<Vec<char>> {
    res.insert(0, " ".repeat(width).chars().collect());
    res
}
pub fn extend_down(mut res: Vec<Vec<char>>, width: usize) -> Vec<Vec<char>> {
    res.push(" ".repeat(width).chars().collect());
    res
}
pub fn extend_right(mut res: Vec<Vec<char>>) -> Vec<Vec<char>> {
    for i in 0..res.len() {
        res[i].push(' ');
    }
    res
}
pub fn extend_left(mut res: Vec<Vec<char>>) -> Vec<Vec<char>> {
    for i in 0..res.len() {
        res[i].insert(0, ' ');
    }
    res
}

pub fn execute(code: &str) -> String {
    let mut res: Vec< Vec<char> > = vec![ vec![ '*' ] ];
    let mut width = 1; let mut height = 1;
    let mut posx = 0; let mut posy = 0;
    let mut rotation = 0;
    let code: Vec<char> = code.chars().collect();
    let mut i = 0; let mut j; let mut counter = 0; 
    while i < code.len(){
        j = i + 1;
        if j < code.len() && code[j].is_ascii_digit() {
            while j < code.len() && code[j].is_ascii_digit(){
                counter = counter * 10 +((code[j] as i32) - 48);
                j+=1;
            }
        }
        else { counter = 1; }
        for _rep in 0..counter {
            match code[i] {
                'L' => { if rotation == 0 { rotation = 3; } else { rotation -= 1; } }
                'R' => { rotation = (rotation + 1) % 4; }
                'F' => {
                    match rotation{
                        0 => {
                            if posx+1 == width { res = extend_right(res); width+=1; posx+=1; }
                            else { posx+=1; }
                            res[posy][posx] = '*';
                        }
                        1 => {
                            if posy+1 == height { res = extend_down(res, width); height+=1; posy+=1; } 
                            else { posy+=1; }
                            res[posy][posx] = '*';                       
                        }
                        2 => {
                            if posx == 0 { res = extend_left(res); width+=1; }
                            else { posx-=1; }                            
                            res[posy][posx] = '*';
                        }
                        3 => {
                            if posy == 0 { res = extend_up(res, width); height+=1; } 
                            else { posy-=1; }                                                        
                            res[posy][posx] = '*';                            
                        }
                        _ => {}
                    }
                }
                _   => {}
            }
        }
        counter = 0;
        i=j;
    }
    let mut s: Vec<String> = vec![];
    for e in res{
        s.push( e.into_iter().collect() );
    }
    s.into_iter().collect::<Vec<String>>().join("\r\n")
}

#[test]
fn test0() { assert_eq!(execute(""), "*"); }
#[test]
fn test1() { assert_eq!(execute("F"), "**"); }
#[test]
fn test2() { assert_eq!(execute("FFF"), "****"); }
#[test]
fn test3() { assert_eq!(execute("F5"), "******"); }
#[test]
fn test4() { assert_eq!(execute("L4"), "*"); }
#[test]
fn test5() { assert_eq!(execute("L4F"), "**"); }
#[test]
fn test6() { assert_eq!(execute("FRFRF"), "**\r\n**"); }
#[test]
fn test7() { assert_eq!(execute("FFRFFRFF"), "***\r\n  *\r\n***"); }
#[test]
fn test8() { assert_eq!(execute("FFFFRFFFFLFF"), "*****  \r\n    *  \r\n    *  \r\n    *  \r\n    ***"); }
#[test]
fn test9() { assert_eq!(execute("F3R2F5R1F2L1"), "*     \r\n*     \r\n******"); }

fn main() {
}
