use regex::Regex;
extern crate chrono;
use chrono::prelude::*;

pub fn format_time(time0: u128) -> String {
    let mut second = time0 / 1000;
    let time = time0 % 1000;
    let min = second / 60;
    second = second % 60;
    let mut text = String::new();
    if min < 10 {text.push('0');}
    text.push_str(&min.to_string());
    text.push(':');
    if second < 10 {text.push('0');}
    text.push_str(&second.to_string());
    text.push('.');
    text.push_str(&time.to_string());
    text
}

pub fn get_time() -> String {
    let mut c = String::new();
    let utc: DateTime<Utc> = Utc::now();
    if utc.hour() < 10 { c.push('0')}
    c.push_str(&utc.hour().to_string()); c.push(':');
    if utc.minute() < 10 { c.push('0')}
    c.push_str(&utc.minute().to_string()); c.push(':');
    if utc.second() < 10 { c.push('0')}
    c.push_str(&utc.second().to_string()); 
    c
}

pub fn check_all(
    name : String,
    surname : String,
    country : String,
    city : String,
    address : String,
    phone : String,
    email : String) -> u8
{
    if name.is_empty() || surname.is_empty() || country.is_empty() || city.is_empty() || address.is_empty() || phone.is_empty() || email.is_empty(){
        return 1;
    }
    let re = Regex::new(r"^\d{3}-\d{3}-\d{3}$").unwrap();
    if !re.is_match(&phone) {
        return 2; 
    }
    0
}