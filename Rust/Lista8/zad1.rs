fn dna_strand(dna: &str) -> String {
    let mut s = String::new();
    for elem in dna.chars() {
        match elem {
        'A' => s.push('T'),
        'T' => s.push('A'),
        'C' => s.push('G'),
        'G' => s.push('C'),
        _   => {}
        }
    }
    s
}
#[test]
fn test0() {
    assert_eq!(dna_strand("A"), "T")
}
#[test]
fn test1() {
    assert_eq!(dna_strand("T"), "A")
}
#[test]
fn test2() {
    assert_eq!(dna_strand("AAA"), "TTT")
}
#[test]
fn test3() {
    assert_eq!(dna_strand("AAATAAA"), "TTTATTT")
}
#[test]
fn test4() {
    assert_eq!(dna_strand("C"), "G")
}
#[test]
fn test5() {
    assert_eq!(dna_strand("G"), "C")
}
#[test]
fn test6() {
    assert_eq!(dna_strand("CGCG"), "GCGC")
}
#[test]
fn test7() {
    assert_eq!(dna_strand("ATCG"), "TAGC")
}
#[test]
fn test8() {
    assert_eq!(dna_strand("ATCGATCG"), "TAGCTAGC")
}
#[test]
fn test9() {
    assert_eq!(dna_strand("AAATCG"), "TTTAGC")
}


fn main() {
}
