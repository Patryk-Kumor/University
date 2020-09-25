fn square_area_to_circle(size:f64) -> f64 {
    std::f64::consts::PI * (size / 4.0)
}

#[test]
fn test0() {
  assert_close(square_area_to_circle(9.0), 7.0685834705770345, 1e-8);
}
#[test]
fn test1() {
  assert_close(square_area_to_circle(20.0), 15.70796326794897, 1e-8);
}
#[test]
fn test2() {
  assert_close(square_area_to_circle(16.0), 12.56637061435917‬, 1e-8);
}

#[test]
fn test3() {
  assert_close(square_area_to_circle(64.0), 50.26548245743669‬, 1e-8);
}
#[test]
fn test4() {
  assert_close(square_area_to_circle(256.0), 201.0619298297467‬, 1e-8);
}