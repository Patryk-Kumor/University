fn interpreter(code: &str, iterations: usize,
               width: usize, height: usize) -> String
{
    let mut res: Vec< Vec<char> > = vec![ ];
        
    for i in 0..height{
        res.push(vec![]);
        for _j in 0..width{
            res[i].push('0');
        }
    }
    
    let mut pos_x = 0;
    let mut pos_y = 0;
    let old_code = code.clone();
    let code: Vec<char> = code.chars().collect();
    let mut i = 0;
    let mut skip: bool = false;
    let iterations = iterations;
    let mut counter = 0;
    
    while (i < code.len())&&(counter < iterations) {
        if i == code.len() { break; }
        
        match code[i] {
            'n' => { if pos_x == 0 {pos_x = height}
                     pos_x -= 1; },
            'e' => { if pos_y == width - 1 {pos_y = 0}
                     else { pos_y += 1; }},
            's' => { if pos_x == height - 1 {pos_x = 0}
                     else { pos_x += 1; }},
            'w' => { if pos_y == 0 {pos_y = width}
                     pos_y -= 1; },
            '*' => { res[pos_x][pos_y] = (res[pos_x][pos_y] as u8 ^ 1) as char; },
            '[' => {
                    if res[pos_x][pos_y] == '0'{
                        while code[i+1] != ']' {
                            i+=1;
                        }
                        i+=1;
                        i = old_code.to_string().find(']').unwrap();
                    }
                   },
            ']' => {
                    if res[pos_x][pos_y] == '1'{
                        while code[i-1] != '[' {
                            i-=1;
                        }
                        i-=1;
                        i = old_code.to_string().find('[').unwrap();
                    }
                   },
            _   => { skip = true; }
        }       
        counter += 1;
        i+=1;         
        if skip { skip = false; counter -= 1; }
        else { skip = false; }
    }   
    let temp: Vec<String> = res.into_iter().map({|e| e.iter().cloned().collect::<String>()}).collect();
    temp.into_iter().collect::<Vec<String>>().join("\r\n")
}

#[test]
fn test0() {
  assert_eq!(interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 1, 6, 2), 
             "100000\r\n000000");
}
#[test]
fn test1() {
  assert_eq!(interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 1, 6, 9), 
             "100000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000");
}
#[test]
fn test2() {
  assert_eq!(interpreter("*e*e*e*e*e*e*e*e*", 6, 6, 1), 
             "111000");
}
#[test]
fn test3() {
  assert_eq!(interpreter("*e*e*e*e*e*e*e*", 0, 6, 1), 
             "000000");
}
#[test]
fn test4() {
  assert_eq!(interpreter("e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 0, 1, 1), 
             "0");
}
#[test]
fn test5() {
  assert_eq!(interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 0, 1, 1), 
             "0");
}
#[test]
fn test6() {
  assert_eq!(interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 0, 6, 9), 
             "000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000");
}
#[test]
fn test7() {
  assert_eq!(interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 7, 6, 9), 
             "111100\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000");
}
#[test]
fn test8() {
  assert_eq!(interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 19, 6, 9), 
             "111100\r\n000010\r\n000001\r\n000010\r\n000100\r\n000000\r\n000000\r\n000000\r\n000000");
}
#[test]
fn test9() {
  assert_eq!(interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 42, 6, 9), 
             "111100\r\n100010\r\n100001\r\n100010\r\n111100\r\n100000\r\n100000\r\n100000\r\n100000");
}

fn main() {
    let x = interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 100, 6, 9);
}
