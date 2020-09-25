fn count_red_beads(n: u32) -> u32 {
    if n < 2 { 0 } else { 2*(n-1) }
}

#[test]
fn test0() {
  assert_eq!(count_red_beads(0), 0);
}
#[test]
fn test1() {
  assert_eq!(count_red_beads(1), 0);
}
#[test]
fn test2() {
  assert_eq!(count_red_beads(2), 2);
}
#[test]
fn test3() {
  assert_eq!(count_red_beads(3), 4);
}
#[test]
fn test4() {
  assert_eq!(count_red_beads(4), 6);
}
