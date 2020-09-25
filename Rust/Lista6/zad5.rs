struct Sudoku{
    data: Vec<Vec<u32>>,
}

impl Sudoku{
    fn is_valid(&self) -> bool {            
    
        if self.data.len() == 1 {
            if self.data[0].len() == 0 { return false; }
            else {
                if self.data[0][0] == 1 { return true; }
                else { return false; }
            }
        }
        if self.data.len() == 2 {
            if self.data[0] == vec![1,2] && self.data[1] == vec![2,1] || self.data[0] == vec![2,1] && self.data[1] == vec![1,2] { 
                return true;
            }
        }
    
        let n: i32 = self.data.len() as i32;
        let square: i32 = (n as f64).sqrt() as i32;
        let copy = self.data.clone();
        let mut check = self.data[0].clone(); check.sort();
        let mut i = 0;
        for mut elem in copy {
            elem.sort();
            if elem != check { return false; }
            let mut temp : Vec<u32> = vec![];
            for j in 0..n { temp.push(self.data[j as usize][i as usize]) }
            temp.sort();
            if elem != temp { return false; }
            if elem.len() != check.len() { return false; }
            if elem.len() != temp.len() { return false; }
            i += 1;
        }
        
        let mut x: usize = 0;
        let y: usize = 0;
        let mut temp2 : Vec<u32> = vec![];
        for x_ in 0..square {
            x = (square as usize)*x;
            for y_ in 0..square {
                y = (square as usize)*x;
                for pos_x in 0..square {   
                    for pos_y in 0..square {
                            temp2.push( self.data[x + pos_x as usize][y + pos_y as usize] );
                    }
                }
                temp2.sort();
                if temp2 != check { return false; }
                temp2 = vec![];
            }
        }
        true
    }
}

#[test]
fn test0() {
    let sudoku = Sudoku{
        data: vec![ vec![] ],
    };
    assert!(!sudoku.is_valid());
}
#[test]
fn test1() {
    let sudoku = Sudoku{
        data: vec![ vec![0] ],
    };
    assert!(!sudoku.is_valid());
}
#[test]
fn test2() {
    let sudoku = Sudoku{
        data: vec![ vec![1] ],
    };
    assert!(sudoku.is_valid());
}
#[test]
fn test3() {
    let sudoku = Sudoku{
        data: vec![ vec![2] ],
    };
    assert!(!sudoku.is_valid());
}
#[test]
fn test4() {
    let sudoku = Sudoku{
        data: vec![ vec![1, 2], vec![2, 1] ],
    };
    assert!(sudoku.is_valid());
}
#[test]
fn test5() {
    let sudoku = Sudoku{
        data: vec![ vec![2, 1], vec![1, 2] ],
    };
    assert!(sudoku.is_valid());
}
#[test]
fn test6() {
    let sudoku = Sudoku{
        data: vec![ vec![1, 2, 3, 4], 
                    vec![3, 4, 1, 2],
                    vec![4, 1, 2, 3],
                    vec![2, 3, 4, 1] ],
    };
    assert!(sudoku.is_valid());
}
#[test]
fn test7() {
    let sudoku = Sudoku{
        data: vec![ vec![1, 1, 3, 4], 
                    vec![3, 4, 1, 2],
                    vec![4, 1, 2, 3],
                    vec![2, 3, 4, 1] ],
    };
    assert!(!sudoku.is_valid());
}
#[test]
fn test8() {
    let sudoku = Sudoku{
        data: vec![ vec![1, 1, 1, 1], 
                    vec![3, 4, 1, 2],
                    vec![4, 1, 2, 3],
                    vec![2, 3, 4, 1] ],
    };
    assert!(!sudoku.is_valid());
}
#[test]
fn test9() {
    let sudoku = Sudoku{
        data: vec![ vec![1, 2, 3, 4], 
                    vec![1, 2, 3, 4],
                    vec![1, 2, 3, 4],
                    vec![1, 2, 3, 4] ],
    };
    assert!(!sudoku.is_valid());
}


fn main() {
}
