require 'dbm'
require 'irb'
require 'set'

$database = DBM.open('baza')  

#przykładowe dane
$database['janek'] = ["Jan Kowalski", "123456789", "email1@wp.pl"]
$database['jan'] = ["Jan Nowak", "987654321", "email2@wp.pl"]
$database['janusz'] = ["Janusz Kowalski", "123789456", "email3@wp.pl"]

def validate_email(email)
    /^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$/ =~ email
end

def validate_number(number)
    /\(?([0-9]{3})\)?([ .-]?)([0-9]{3})\2([0-9]{4})/ =~ number or /\(?([0-9]{3})\)?([ .-]?)([0-9]{3})\2([0-9]{3})/ =~ number
end

def dodaj()
    print "Podaj unikalną nazwę dla nowego rekordu: "
    nick = gets.chomp
    if $database[nick]
        return "Nie dodano, ten rekord już istnieje"
    end
    print "Podaj jego pełne imię i nazwisko: "
    nazwa = gets.chomp
    print "Podaj jego numer: "
    numer = gets.chomp
    while !validate_number(numer)
        print "Numer jest niepoprawny, podaj poprawny numer: "
        numer = gets.chomp
    end
    print "Podaj jego email: "
    email = gets.chomp
    while !validate_email(email)
        print "Email jest niepoprawny, podaj poprawny email: "
        email = gets.chomp
    end
    $database[nick] = [nazwa, numer, email]
    "Dodano"
end

def szukaj(nick)
    if $database[nick]
        $database[nick]
    else
        "Nie znaleziono takiego nicku"
    end
end

def szukaj_podobne(regexp)
    $database.each { | k, v | puts "#{k} => #{v.to_s}" if ((regexp =~ k) or (regexp =~ v.to_s))}
    "Wyświetlono wszystko"
end

def wypisz_wszystko()
    $database.each { | k, v | puts "#{k} => #{v.to_s}" }
    "Wyświetlono wszystko"
end

def usun(nick)
    if $database[nick]
        $database.delete(nick)
        "Usunięto"
    else
        "Nie znaleziono"
    end
end

#"Menu"
print "--------------------------------------------------------------------\n"
print "Załadowano program notatnik\n\n"
print "Dostępne polecenia to:\n"
print "- dodaj\n- szukaj(nick)\n- szukaj_podobne(wyr_reg)\n- wypisz_wszystko\n- usun(nick)\n"
print "--------------------------------------------------------------------\n"
# Wywołanie irb zachowujące lokalne zmienne 
# -> pomocne przy wywoływaniu z konsoli
IRB.setup(nil)
irb = IRB::Irb.new(nil)
IRB.conf[:MAIN_CONTEXT] = irb.context
irb.context.workspace = IRB::WorkSpace.new(binding)
trap 'INT' do
   irb.signal_handle
end
catch(:IRB_EXIT) { irb.eval_input }