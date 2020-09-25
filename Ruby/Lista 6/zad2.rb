require 'dbm'
require 'irb'
require 'date'


$database = DBM.open('baza_cd')  



def dodaj()
    print "Podaj unikalną nazwę dla nowego rekordu: "
    id = gets.chomp
    if $database[id]
        return "Nie dodano, ten rekord już istnieje"
    end
    print "Podaj nazwę płyty cd:"
    nazwa = gets.chomp
    print "Podaj autora/autorów:"
    autor = gets.chomp
    print "Podaj gatunek albumu: "
    gatunek = gets.chomp
    print "Podaj listę utworów (po przecinku): "
    piosenki = gets.chomp.split(',')
    $database[id] = [nazwa, autor, gatunek, piosenki, "false"]
    "Dodano"
end

def wypozycz(id, komu, data_wyp)
    tab = $database['id'].to_s[1...-1].gsub!(/\"/, '')
    tab_lista = tab.scan(/\[([^"]*)\]/)[0]
    tab_lista = tab_lista[0].split(', ')
    #print tab_lista
    #print "\n"
    tab = tab.gsub!(/\[([^"]*)\]\,./, '').split(', ')
    #print tab
    #print "\n"
    finish = tab[0...-1] + [tab_lista] + [ komu+" "+data_wyp ]
    #print finish
    $database[id] = finish
    "Zmieniono"
end

def oddanie(id)
    tab = $database['id'].to_s[1...-1].gsub!(/\"/, '')
    tab_lista = tab.scan(/\[([^"]*)\]/)[0]
    tab_lista = tab_lista[0].split(', ')
    #print tab_lista
    #print "\n"
    tab = tab.gsub!(/\[([^"]*)\]\,./, '').split(', ')
    #print tab
    #print "\n"
    finish = tab[0...-1] + [tab_lista] + [ "false" ]
    #print finish
    $database[id] = finish
    "Zmieniono"
end

def wypisz_wszystko()
    $database.each { | k, v | puts "#{k} => #{v.to_s}" }
    "Wyświetlono wszystko"
end

def szukaj(id)
    if $database[id]
        $database[id]
    else
        "Nie znaleziono takiego nicku"
    end
end

def szukaj_podobne(regexp)
    $database.each { | k, v | puts "#{k} => #{v.to_s}" if ((regexp =~ k) or (regexp =~ v.to_s))}
    "Wyświetlono wszystko"
end

def usun(id)
    if $database[id]
        $database.delete(id)
        "Usunięto"
    else
        "Nie znaleziono"
    end
end

def po_terminie(id)
    tab = $database[id].to_s[1...-1].gsub!(/\"/, '').split(', ')
    finish = tab[-1]
    wyr = /(\d\d\d\d)-(\d\d)-(\d\d)/
    #"rrrr-mm-dd"
    date = Date.today().to_s.split('-')
    w = finish.scan(wyr)[0] 
    if !w.nil? and w.length==3 
        if w[0].to_i < date[0].to_i
            print "\nPo terminie\n"
            true
        else
            if w[1].to_i < date[1].to_i
                print "\nPo terminie\n"
                true
            else
                if w[2].to_i <= date[2].to_i
                    print "\nPo terminie\n"
                    true
                else
                    true
                end
                true
            end
            true
        end
        #print w.to_s + " - " + date
    else
        false
    end
end

def zestawienie()
    $database.each { | k, v | puts "#{k} => #{v.to_s}\n"if po_terminie(k) }
    "Wszystkie te albumy były wypożyczone"
end

#przykładowe dane
info = false
$database['the_works'] = ["The Works", "Queen", "rock", ["Radio Ga Ga", "Tear It Up", "It's a Hard Life", "Man on the Prowl"], "false"]
$database['the_miracle'] = ["The Miracle", "Queen", "rock", ["Party", "Khashoggi's Ship", "The Miracle", "I Want It All"], "false"]

wypozycz("the_works", "Adam", "2018-11-25")
#"Menu"
print "--------------------------------------------------------------------\n"
print Date.today().to_s
print "\nZaładowano program notatnik, wszystkie dane pobrano z pliku data.txt\n\n"
print "Dostępne polecenia to:\n"
print "- dodaj\n- wypisz_wszystko\n- wypozycz(id, komu, 'rrrr-mm-dd')\n- oddaj(id)\n- szukaj(id)\n- szukaj_podobne(wyr_reg)\n- usun(id)\n- zestawienie\n"
print "\n--------------------------------------------------------------------\n"
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