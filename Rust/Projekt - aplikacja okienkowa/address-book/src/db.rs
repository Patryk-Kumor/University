extern crate rustbreak;
extern crate failure;

use rustbreak::FileDatabase;
use rustbreak::deser::Ron;
use std::collections::HashMap;

#[derive(Eq, PartialEq, Debug, Serialize, Deserialize, Clone)]
pub struct Person {
    pub name: String,
    pub surname: String,
    pub country: String,
    pub city: String,
    pub address: String,
    pub phone: String,
    pub email: String,
}

pub fn read_list(path: String) -> Result< Vec<String>, failure::Error>  {
    let db = FileDatabase::<HashMap<String, Person>, Ron>::from_path(path, HashMap::new())?;
    db.load()?;
    let mut res: Vec<String> = vec![];
    db.read(|db| {
        for elem in db { 
            res.push(elem.0.to_string());
        }
    })?;
    res.sort();
    Ok(res)
}

pub fn read_concact(path: String, search: String) -> Result< (Person), failure::Error> {
    let db = FileDatabase::<HashMap<String, Person>, Ron>::from_path(path, HashMap::new())?;
    db.load()?;
    let mut res : Person = Person {
        name: String::new(),
        surname: String::new(),
        country: String::new(),
        city: String::new(),
        address: String::new(),
        phone: String::new(),
        email: String::new()};
    db.read(|db| {
        res = db.get(&search).unwrap().clone() ;
    })?;
    Ok(res.clone())
}

pub fn delete_contact(path: String, search: String) -> Result< (), failure::Error> {
    let db = FileDatabase::<HashMap<String, Person>, Ron>::from_path(path, HashMap::new())?;
    db.load()?;
    let mut new_data : HashMap<String, Person> = HashMap::new();
    db.read(|db| {
        new_data = db.clone();
    })?;
    new_data.remove(&search);
    db.put_data(new_data, true)?; db.save()?;
    Ok(())
}

pub fn add_contact(path: String, search: String, person: Person) -> Result< (bool), failure::Error> {
    let db = FileDatabase::<HashMap<String, Person>, Ron>::from_path(path, HashMap::new())?;
    db.load()?;
    let mut check : bool = true;
    db.read(|db| {
        for elem in db {
            if elem.0.to_string() == search {
                check = false;
            }
        }
    })?;
    if check {
        db.write(|db| {
            db.insert(search.into(), person);
        })?;
        db.save()?;
        return Ok(true);
    }
    else {
        return Ok(false);
    }
}