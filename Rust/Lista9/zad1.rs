fn part_list(arr: Vec<&str>) -> String {
    let mut ret = String::new();
    
    for i in 1..(arr.len()) {
        ret.push('(');
        ret.push_str( &arr[0..i].to_vec().into_iter().collect::<Vec<&str>>().join(" ")  );
        ret.push_str(", ");
        ret.push_str( &arr[i..arr.len()].to_vec().into_iter().collect::<Vec<&str>>().join(" ")  );
        ret.push(')'); 
    }
    ret
}

#[test]
fn test0() {
    assert_eq!(part_list(vec!["I", "wish", "I", "hadn't", "come"]), "(I, wish I hadn\'t come)(I wish, I hadn\'t come)(I wish I, hadn\'t come)(I wish I hadn\'t, come)" );	
}
#[test]
fn test1() {
    assert_eq!(part_list(vec!["A"]), "" );	
}
#[test]
fn test2() {
    assert_eq!(part_list(vec!["A", "B", "C"]), "(A, B C)(A B, C)" );	
}
#[test]
fn test3() {
    assert_eq!(part_list(vec!["A", "B", "C", "A", "B", "C"]), "(A, B C A B C)(A B, C A B C)(A B C, A B C)(A B C A, B C)(A B C A B, C)" );	
}
#[test]
fn test4() {
    assert_eq!(part_list(vec!["A", "B", "C", "C"]), "(A, B C C)(A B, C C)(A B C, C)" );	
}
#[test]
fn test5() {
    assert_eq!(part_list(vec!["A", "B", "C", "C", "C"]), "(A, B C C C)(A B, C C C)(A B C, C C)(A B C C, C)" );	
}
#[test]
fn test6() {
    assert_eq!(part_list(vec!["A", "A"]), "(A, A)" );	
}
#[test]
fn test7() {
    assert_eq!(part_list(vec!["I", "wish"]), "(I, wish)" );	
}
#[test]
fn test8() {
    assert_eq!(part_list(vec!["cdIw", "tzIy", "xDu", "rThG"]), "(cdIw, tzIy xDu rThG)(cdIw tzIy, xDu rThG)(cdIw tzIy xDu, rThG)" );	
}
#[test]
fn test9() {
    assert_eq!(part_list(vec!["I", "wish", "I", "hadn't", "come"]), "(I, wish I hadn\'t come)(I wish, I hadn\'t come)(I wish I, hadn\'t come)(I wish I hadn\'t, come)" );	
}

fn main() {
}
