#[macro_use] extern crate serde_derive;
#[macro_use] extern crate native_windows_gui as nwg;

mod lib;
mod db;
pub use self::db::Person;
extern crate chrono;
use nwg::{Event, Ui, EventArgs, simple_message, fatal_message, dispatch_events};
use nwg::constants::{FileDialogAction, PickerDate, HTextAlign};
use AppId::*; 
use chrono::prelude::*;

#[derive(Debug, Clone, Hash)]
pub enum AppId {
    // Controls
    Label(u8),
    // Main Window
    MainWindow, 
    MenuOptions, MenuFile, MenuCalendar,
    NameList,
    ButtonDelete, ButtonAdd, ButtonEdit,
    FilePath,
    // Contact Window
    ContactWindow, 
    InfoTextName, InfoTextSurname, InfoTextCountry, InfoTextCity, InfoTextAddress, InfoTextPhone, InfoTextEmail,
    ContactWindowButton,
    // Contact Edit Window
    ContactEditWindow, 
    InfoEditName, InfoEditSurname, InfoEditCountry, InfoEditCity, InfoEditAddress, InfoEditPhone, InfoEditEmail,
    ContactEditWindowButton,
    // Calendar Window
    CalendarWindow, Date, Clock, TimerText, TimerButtonStart, TimerButtonReset,
    // Events
    ChooseFile, ChooseContact, 
    AddContact, DeleteContact, EditContact,
    SaveContact, SaveEditedContact,
    StartTimer, ResetTimer, UpdateTimer, UpdateClock,
    // Resources
    BigClockFont, ClockFont, BigFont, TextFont, ButtonFont, 
    // Other
    FileDialog, 
    // Globals
    ClockTimer, Timer
}

nwg_template!(
    head: setup_ui<AppId>,
    controls: [
        // ----
        // REST
        (Timer, nwg_timer!(interval=50)),
        (ClockTimer, nwg_timer!(interval=1000)),
        // ---------------------
        // Okno główne aplikacji
        (MainWindow, nwg_window!( 
            title="Książka adresowa"; size=(470, 420) )),
        (MenuOptions, nwg_menu!(
            parent=MainWindow; text="Opcje")),
        (MenuFile, nwg_menuitem!(
            parent=MenuOptions; text="Wybierz plik bazy danych")),        
        (MenuCalendar, nwg_menuitem!(
            parent=MainWindow; text="Kalendarz i zegar")),
        (Label(0), nwg_label!(
            parent=MainWindow; position=(11,13); size=(90,30); text="Baza danych:"; font=Some(TextFont))),
        (FilePath, nwg_textinput!(
            parent=MainWindow; position=(111, 10); size=(346, 24); readonly=true; font=Some(TextFont))),
        (NameList, nwg_listbox!(
            parent=MainWindow; position=(11, 45); size=(445, 265); font=Some(BigFont);
            collection = vec![].into_iter().collect::<Vec<String>>())),
        (ButtonDelete, nwg_button!(
            parent=MainWindow; position=(10, 310); size=(150, 80);  font=Some(ButtonFont); text="Usuń wpis")),
        (ButtonAdd, nwg_button!(
            parent=MainWindow; position=(160, 310); size=(150, 80); font=Some(ButtonFont); text="Dodaj wpis")),
        (ButtonEdit, nwg_button!(
            parent=MainWindow; position=(310, 310); size=(150, 80); font=Some(ButtonFont); text="Edytuj wpis")),
        // ---------------------------
        // Okno wyświetlające kontakty
        (ContactWindow, nwg_window!( 
            title="Kontakt"; exit_on_close=false; size=(450, 385); visible=false)), 
        (ContactWindowButton, nwg_button!(
            parent=ContactWindow; text="Edytuj wpis"; font=Some(ButtonFont); position=(290, 295); size=(150, 80))),
        (Label(1), nwg_label!(parent=ContactWindow; position=(10,13); size=(120,30); text="Imię:";   font=Some(BigFont))),
        (InfoTextName, nwg_textbox!(
            parent=ContactWindow; position=(140, 10); size=(300, 35); readonly=true; text="Zbigniew"; font=Some(BigFont))),
        (Label(2), nwg_label!(parent=ContactWindow; position=(10,53); size=(120,30); text="Nazwisko:";  font=Some(BigFont))),
        (InfoTextSurname, nwg_textbox!(
            parent=ContactWindow; position=(140, 50); size=(300, 35); readonly=true; text="Stonoga"; font=Some(BigFont))),
        (Label(3), nwg_label!(parent=ContactWindow; position=(10,93); size=(120,30); text="Kraj:";  font=Some(BigFont))),
        (InfoTextCountry, nwg_textbox!(
            parent=ContactWindow; position=(140, 90); size=(300, 35); readonly=true; text="Polska"; font=Some(BigFont))),
        (Label(4), nwg_label!(parent=ContactWindow; position=(10,133); size=(120,30); text="Miasto:";  font=Some(BigFont))),
        (InfoTextCity, nwg_textbox!(
            parent=ContactWindow; position=(140, 130); size=(300, 35); readonly=true; text="Wrocław"; font=Some(BigFont))),
        (Label(5), nwg_label!(parent=ContactWindow; position=(10,173); size=(120,30); text="Adres:";  font=Some(BigFont))),
        (InfoTextAddress, nwg_textbox!(
            parent=ContactWindow; position=(140, 170); size=(300, 35); readonly=true; text="Zielińskiego 13/2"; font=Some(BigFont))),
        (Label(6), nwg_label!(parent=ContactWindow; position=(10,213); size=(120,30); text="Telefon:";  font=Some(BigFont))),
        (InfoTextPhone, nwg_textbox!(
            parent=ContactWindow; position=(140, 210); size=(300, 35); readonly=true; text="123-345-567"; font=Some(BigFont))),
        (Label(7), nwg_label!(parent=ContactWindow; position=(10,253); size=(120,30); text="Email:";  font=Some(BigFont))),
        (InfoTextEmail, nwg_textbox!(
            parent=ContactWindow; position=(140, 250); size=(300, 35); readonly=true; text="zbigniew.s@gov.pl"; font=Some(BigFont))),
        // --------------------------------
        // Okno edytujące/dodające kontakty
        (ContactEditWindow, nwg_window!( 
            title="Dodaj/edytuj kontakt"; exit_on_close=false; size=(450, 385); visible=false)),
        (ContactEditWindowButton, nwg_button!(
            parent=ContactEditWindow; text="Aktualizuj wpis"; font=Some(ButtonFont); position=(290, 295); size=(150, 80))),
        (Label(11), nwg_label!(parent=ContactEditWindow; position=(10,13); size=(120,30); text="Imię:"; font=Some(BigFont))),
        (InfoEditName, nwg_textbox!(
            parent=ContactEditWindow; position=(140, 10); size=(300, 35); readonly=false; text="Zbigniew"; font=Some(BigFont))),
        (Label(12), nwg_label!(parent=ContactEditWindow; position=(10,53); size=(120,30); text="Nazwisko:";  font=Some(BigFont))),
        (InfoEditSurname, nwg_textbox!(
            parent=ContactEditWindow; position=(140, 50); size=(300, 35); readonly=false; text="Stonoga"; font=Some(BigFont))),
        (Label(13), nwg_label!(parent=ContactEditWindow; position=(10,93); size=(120,30); text="Kraj:";  font=Some(BigFont))),
        (InfoEditCountry, nwg_textbox!(
            parent=ContactEditWindow; position=(140, 90); size=(300, 35); readonly=false; text="Polska"; font=Some(BigFont))),
        (Label(14), nwg_label!(parent=ContactEditWindow; position=(10,133); size=(120,30); text="Miasto:";  font=Some(BigFont))),
        (InfoEditCity, nwg_textbox!(
            parent=ContactEditWindow; position=(140, 130); size=(300, 35); readonly=false; text="Wrocław"; font=Some(BigFont))),
        (Label(15), nwg_label!(parent=ContactEditWindow; position=(10,173); size=(120,30); text="Adres:";  font=Some(BigFont))),
        (InfoEditAddress, nwg_textbox!(
            parent=ContactEditWindow; position=(140, 170); size=(300, 35); readonly=false; text="Zielińskiego 13/2"; font=Some(BigFont))),
        (Label(16), nwg_label!(parent=ContactEditWindow; position=(10,213); size=(120,30); text="Telefon:";  font=Some(BigFont))),
        (InfoEditPhone, nwg_textbox!(
            parent=ContactEditWindow; position=(140, 210); size=(300, 35); readonly=false; text="123-345-567"; font=Some(BigFont))),
        (Label(17), nwg_label!(parent=ContactEditWindow; position=(10,253); size=(120,30); text="Email:";  font=Some(BigFont))),
        (InfoEditEmail, nwg_textbox!(
            parent=ContactEditWindow; position=(140, 250); size=(300, 35); readonly=false; text="zbigniew.s@gov.pl"; font=Some(BigFont))),
        // ------------------------
        // Okno kalendarza i zegara
        (CalendarWindow, nwg_window!( 
            title="Kalendarz i zegar"; exit_on_close=false; size=(640, 500); visible=false)),
        (Clock, nwg_label!(parent=CalendarWindow; text="00:00:00"; position=(20, 20); size=(600, 200); align=HTextAlign::Center; font=Some(BigClockFont))),
        (TimerText, nwg_label!(parent=CalendarWindow; text="00:00:00"; position=(300, 240); size=(250, 100); align=HTextAlign::Center; font=Some(ClockFont))),
        (TimerButtonStart, nwg_button!(
            parent=CalendarWindow; position=(170, 220); size=(100, 50); font=Some(ButtonFont); text="START")),
        (TimerButtonReset, nwg_button!(
            parent=CalendarWindow; position=(170, 275); size=(100, 50); font=Some(ButtonFont); text="RESET")),
        (Date, nwg_datepicker!(parent=CalendarWindow; value=Some(PickerDate{year:2020, month:1, day:1});
            format="dd MMMM yyyy"; position=(20, 410); size=(600, 70); font=Some(ClockFont))),
        // -----------------
        // Okno wyboru pliku
        (FileDialog, nwg_filedialog!(parent=Some(MainWindow); action=FileDialogAction::Open; filters=Some("Test(*.ron)|Any(*.*)")))
    ];
    events: [
        // Wybór bazy danych
        (MenuFile, ChooseFile, Event::Triggered, |app,_,_,_|{
            let dialog = nwg_get_mut!(app; (FileDialog, nwg::FileDialog));
            // Jeśli FileDialog pomyślny - czyli wybrano plik z rozszerzeniem .ron
            if dialog.run() {
                // Zapis nowej ścieżki w polu ze ścieżką do pliku
                let text_path = nwg_get!(app; (FilePath, nwg::TextInput));
                text_path.set_text(&dialog.get_selected_item().unwrap());
                // Update listy kontaktów
                let file_path = nwg_get!(app; (FilePath, nwg::TextInput));
                let contact_list = db::read_list(file_path.get_text());
                let mut listbox = nwg_get_mut!(app; (NameList, nwg::ListBox<String>));
                listbox.clear();
                for elem in contact_list.unwrap() { listbox.push(elem); }
                listbox.sync();
            }
            else {
                simple_message("Komunikat bazy danych", "Aby kontynuować, należy wybrać poprawny plik bazy danych w formacie .ron" );
            }
        }),
        // Otwieranie okna z kalendarzem
        (MenuCalendar, ChooseFile, Event::Triggered, |app,_,_,_|{
            let date = nwg_get_mut!(app; (Date, nwg::DatePicker));
            let utc: DateTime<Utc> = Utc::now();
            date.set_value(&Some(PickerDate{year:utc.year() as u16, month:utc.month() as u16, day:utc.day() as u16 }));
            let calendar_window = nwg_get_mut!(app; (CalendarWindow, nwg::Window));
            let mut clock_timer = nwg_get_mut!(app; (ClockTimer, nwg::Timer));
            if clock_timer.running() {
            }
            else{
                clock_timer.start();
            }            
            calendar_window.set_visibility(true);
        }),
        // Wybór kontaktu do wyświetlenia
        (NameList, ChooseContact, Event::DoubleClick, |app,_,_,_| {
            let list_box = nwg_get_mut!(app; (NameList, nwg::ListBox<String>));
            let contact_window = nwg_get_mut!(app; (ContactWindow, nwg::Window));
            let file_path = nwg_get!(app; (FilePath, nwg::TextInput));
            // Odczyt który z kontaktów był kliknięty
            let index = list_box.get_selected_index().unwrap();
            let search = list_box.get_string(index).unwrap();
            // Odczyt z bazy danych
            let person = db::read_concact(file_path.get_text(), search).unwrap();
            // Nadanie nowych wartości w okienku
            let name = nwg_get_mut!(app; (InfoTextName, nwg::TextBox));
            name.set_text(&person.name);
            let surname = nwg_get_mut!(app; (InfoTextSurname, nwg::TextBox));
            surname.set_text(&person.surname);
            let country = nwg_get_mut!(app; (InfoTextCountry, nwg::TextBox));
            country.set_text(&person.country);
            let city = nwg_get_mut!(app; (InfoTextCity, nwg::TextBox));
            city.set_text(&person.city);
            let address = nwg_get_mut!(app; (InfoTextAddress, nwg::TextBox));
            address.set_text(&person.address);
            let phone = nwg_get_mut!(app; (InfoTextPhone, nwg::TextBox));
            phone.set_text(&person.phone);
            let email = nwg_get_mut!(app; (InfoTextEmail, nwg::TextBox));
            email.set_text(&person.email);
            // Otwieranie okna
            contact_window.set_visibility(true);
        }),
        // Otwarcie nowego okna z pustymi polami do wypełnienia
        (ButtonAdd, AddContact, Event::Click, |app,_,_,_| {
            let clean_contact_window = nwg_get_mut!(app; (ContactEditWindow, nwg::Window));
            // Czyszczenie wartości w okienku
            let name = nwg_get_mut!(app; (InfoEditName, nwg::TextBox));
            name.set_text("");
            let surname = nwg_get_mut!(app; (InfoEditSurname, nwg::TextBox));
            surname.set_text("");
            let country = nwg_get_mut!(app; (InfoEditCountry, nwg::TextBox));
            country.set_text("");
            let city = nwg_get_mut!(app; (InfoEditCity, nwg::TextBox));
            city.set_text("");
            let address = nwg_get_mut!(app; (InfoEditAddress, nwg::TextBox));
            address.set_text("");
            let phone = nwg_get_mut!(app; (InfoEditPhone, nwg::TextBox));
            phone.set_text("");
            let email = nwg_get_mut!(app; (InfoEditEmail, nwg::TextBox));
            email.set_text("");
            // Otwarcie okna
            clean_contact_window.set_visibility(true);
        }),
        // Otwarcie okna z danymi zaznaczonego kontaktu
        (ButtonEdit, EditContact, Event::Click, |app,_,_,_| {
            let list_box = nwg_get_mut!(app; (NameList, nwg::ListBox<String>));
            let edit_contact_window = nwg_get_mut!(app; (ContactEditWindow, nwg::Window));
            let file_path = nwg_get!(app; (FilePath, nwg::TextInput));
            // Odczyt który z kontaktów był kliknięty
            if list_box.get_selected_index() == None{
                simple_message("Komunikat edytora", "Aby kontynuować, należy zaznaczyć wybrany kontakt na liście" );
            } 
            else {
                let index = list_box.get_selected_index().unwrap();
                let search = list_box.get_string(index).unwrap();
                let search2 = search.clone();
                // Odczyt z bazy danych
                let person = db::read_concact(file_path.get_text(), search).unwrap();
                // Nadanie nowych wartości w okienku
                let name = nwg_get_mut!(app; (InfoEditName, nwg::TextBox));
                name.set_text(&person.name);
                let surname = nwg_get_mut!(app; (InfoEditSurname, nwg::TextBox));
                surname.set_text(&person.surname);
                let country = nwg_get_mut!(app; (InfoEditCountry, nwg::TextBox));
                country.set_text(&person.country);
                let city = nwg_get_mut!(app; (InfoEditCity, nwg::TextBox));
                city.set_text(&person.city);
                let address = nwg_get_mut!(app; (InfoEditAddress, nwg::TextBox));
                address.set_text(&person.address);
                let phone = nwg_get_mut!(app; (InfoEditPhone, nwg::TextBox));
                phone.set_text(&person.phone);
                let email = nwg_get_mut!(app; (InfoEditEmail, nwg::TextBox));
                email.set_text(&person.email);
                // Usunięcie z bazy danych
                db::delete_contact(file_path.get_text(), search2).unwrap();
                // Otwarcie okna
                edit_contact_window.set_visibility(true);   
            }       
        }),     
        //  Usunięcie zaznaczonego kontaktu
        (ButtonDelete, DeleteContact, Event::Click, |app,_,_,_| {
            let mut list_box = nwg_get_mut!(app; (NameList, nwg::ListBox<String>));
            let file_path = nwg_get!(app; (FilePath, nwg::TextInput));
            // Odczyt który z kontaktów był kliknięty
            if list_box.get_selected_index() == None {
                simple_message("Komunikat edytora", "Aby usunąć rekord, należy zaznaczyć wybrany kontakt na liście" );
            }
            else {
                // Odczyt który z kontaktów był kliknięty
                let index = list_box.get_selected_index().unwrap();
                let search = list_box.get_string(index).unwrap();
                // Usunięcie z bazy danych
                db::delete_contact(file_path.get_text(), search).unwrap();
                // Update listy kontaktów
                let contact_list = db::read_list(file_path.get_text());
                list_box.clear();
                for elem in contact_list.unwrap() { list_box.push(elem); }
                list_box.sync();
            }
        }),
        // Okno z przyciskiem "EDYTUJ"
        (ContactWindowButton, SaveContact, Event::Click, |app,_,_,_| {
            let show_contact_window = nwg_get_mut!(app; (ContactWindow, nwg::Window));
            let edit_contact_window = nwg_get_mut!(app; (ContactEditWindow, nwg::Window));
            let file_path = nwg_get!(app; (FilePath, nwg::TextInput));
            // Odczyt danych z akutalnego okna
            let name = nwg_get_mut!(app; (InfoTextName, nwg::TextBox));
            let surname = nwg_get_mut!(app; (InfoTextSurname, nwg::TextBox));
            let mut search = name.get_text(); search.push(' '); search.push_str(&surname.get_text());
            let search2 = search.clone();
            // Odczyt z bazy danych
            let person = db::read_concact(file_path.get_text(), search).unwrap();
            // Zamknięcie okna
            show_contact_window.set_visibility(false);
            // Usunięcie z bazy danych
            db::delete_contact(file_path.get_text(), search2).unwrap();
            // Nadanie nowych wartości w okienku
            let name = nwg_get_mut!(app; (InfoEditName, nwg::TextBox));
            name.set_text(&person.name);
            let surname = nwg_get_mut!(app; (InfoEditSurname, nwg::TextBox));
            surname.set_text(&person.surname);
            let country = nwg_get_mut!(app; (InfoEditCountry, nwg::TextBox));
            country.set_text(&person.country);
            let city = nwg_get_mut!(app; (InfoEditCity, nwg::TextBox));
            city.set_text(&person.city);
            let address = nwg_get_mut!(app; (InfoEditAddress, nwg::TextBox));
            address.set_text(&person.address);
            let phone = nwg_get_mut!(app; (InfoEditPhone, nwg::TextBox));
            phone.set_text(&person.phone);
            let email = nwg_get_mut!(app; (InfoEditEmail, nwg::TextBox));
            email.set_text(&person.email);
            // Otwarcie drugiego okna
            edit_contact_window.set_visibility(true);   
        }),
        // Okno z przyciskiem "AKTUALIZUJ WPIS"
        (ContactEditWindowButton, SaveEditedContact, Event::Click, |app,_,_,_| {
            let edit_contact_window = nwg_get_mut!(app; (ContactEditWindow, nwg::Window));
            let name = nwg_get_mut!(app; (InfoEditName, nwg::TextBox)).get_text();
            let surname = nwg_get_mut!(app; (InfoEditSurname, nwg::TextBox)).get_text();
            let country = nwg_get_mut!(app; (InfoEditCountry, nwg::TextBox)).get_text();
            let city = nwg_get_mut!(app; (InfoEditCity, nwg::TextBox)).get_text();
            let address = nwg_get_mut!(app; (InfoEditAddress, nwg::TextBox)).get_text();
            let phone = nwg_get_mut!(app; (InfoEditPhone, nwg::TextBox)).get_text();
            let email = nwg_get_mut!(app; (InfoEditEmail, nwg::TextBox)).get_text();
            let file_path = nwg_get!(app; (FilePath, nwg::TextInput));
            if file_path.get_text() == "" {
                simple_message("Komunikat edytora", "Do programu nie załadowano bazy danych" );
            }
            // Sprawdzanie poprawności
            match lib::check_all(name.clone(),surname.clone(),country.clone(),city.clone(),address.clone(),phone.clone(),email.clone())
            { 
                0 => {
                    let mut search = String::new();
                    search.push_str(&name); search.push(' '); search.push_str(&surname);
                    let res : Person = Person {
                        name: String::from(name),
                        surname: String::from(surname),
                        country: String::from(country),
                        city: String::from(city),
                        address: String::from(address),
                        phone: String::from(phone),
                        email: String::from(email)};
                    match db::add_contact(file_path.get_text(), search, res) {
                        Ok(true) => {
                            // Zamknięcie okna 
                            edit_contact_window.set_visibility(false);
                            // Update listy 
                            let contact_list = db::read_list(file_path.get_text());
                            let mut listbox = nwg_get_mut!(app; (NameList, nwg::ListBox<String>));
                            listbox.clear();
                            for elem in contact_list.unwrap() { listbox.push(elem); }
                            listbox.sync();
                        },
                        Ok(false) => {
                            simple_message("Komunikat edytora", "Wpis o takiej nazwie już istnieje" );
                        },
                        _ => {}
                    };
                }, 
                1 => { simple_message("Komunikat edytora", "Pola nie mogą być puste" ); }
                2 => { simple_message("Komunikat edytora", "Niepoprawny format telefonu" ); }
                _ => { simple_message("Komunikat edytora", "Wpisane dane są niepoprawne" ); }
            }
        }),
        (TimerButtonStart, StartTimer, Event::Click, |app,_,_,_|{
            let mut timer = nwg_get_mut!(app; (Timer, nwg::Timer));
            let btn = nwg_get_mut!(app; (TimerButtonStart, nwg::Button));
            if timer.running() {
                btn.set_text("START");
                timer.stop();
            } else {
                btn.set_text("STOP");
                timer.start();
            }
        }),
        (TimerButtonReset, ResetTimer, Event::Click, |app,_,_,_|{
            let mut timer = nwg_get_mut!(app; (Timer, nwg::Timer));
            let timer_text = nwg_get!(app; (TimerText, nwg::Label));
            timer_text.set_text(format!("00:00.00{:?}", 0).as_ref());
            if timer.running() {
                timer.stop(); timer.start();
            }
            else{
                timer.start(); timer.stop();
            }
        }),
        (Timer, UpdateTimer, Event::Tick, |app,_,_,args|{
            let timer_text = nwg_get!(app; (TimerText, nwg::Label));
            let elapsed = match args { 
                &EventArgs::Tick(ref d) => d,
                _ => unreachable!()
            };
            let time = elapsed.as_millis();
            let text = lib::format_time(time);
            timer_text.set_text(&text);
        }),
        (ClockTimer, UpdateClock, Event::Tick, |app,_,_,_|{
            let clock_text = nwg_get!(app; (Clock, nwg::Label));
            let time = lib::get_time();
            clock_text.set_text(&time);
            let date = nwg_get_mut!(app; (Date, nwg::DatePicker));
            let utc: DateTime<Utc> = Utc::now();
            date.set_value(&Some(PickerDate{year:utc.year() as u16, month:utc.month() as u16, day:utc.day() as u16 }));
        })
    ];
    resources: [
        (BigClockFont, nwg_font!(family="Arial"; size=150)),
        (ClockFont, nwg_font!(family="Arial"; size=60)),
        (BigFont, nwg_font!(family="Arial"; size=30)),
        (ButtonFont, nwg_font!(family="Arial"; size=23)),
        (TextFont, nwg_font!(family="Arial"; size=17))
    ];
    values: [  
    ]
);

fn main() {
    let app: Ui<AppId>;

    match Ui::new() {
        Ok(_app) => { app = _app; },
        Err(e) => { fatal_message("Fatal Error", &format!("{:?}", e) ); }
    }

    if let Err(e) = setup_ui(&app) {
        fatal_message("Fatal Error", &format!("{:?}", e));
    }

    dispatch_events();
}
