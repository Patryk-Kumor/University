require 'irb'
require 'set'

def dodaj()
    print "Podaj nazwę dla nowego rekordu: "
    nick = gets.chomp
    if $database[nick]
        "Nie dodano, ten rekord już istnieje"
    end
    print "Podaj jego numer: "
    numer = gets.chomp
    print "Podaj do jakich grup należy (po przecinku, małymi literami, bez spacji): " 
    tagi = gets.chomp
    File.open("C:/Users/Patryk/Desktop/data.txt", "a") do |f|
        f.puts nick + ";" + numer + ";" + tagi
    end
    tagi = tagi.split(',')
    $database[nick] = [numer] + tagi
    for tag in tagi
        if $database_group[tag] 
           $database_group[tag] = $database_group[tag].add(nick)
        else
           $database_group[tag] = Set.new()
           $database_group[tag] = $database_group[tag].add(nick)
        end
      end
    "Dodano"
end

def znajdz(nick)
    lista = ""
    for e in $database[nick][1]
        lista += e + ", "
    end
    lista = lista.chomp(", ") 
    print "Grupy dla <#{nick}> to [#{lista}]\n"
    "Zapisany numer dla <#{nick}> to #{$database[nick][0]}"
end

def wypisz()
    lista = ""
    for e in $database_group
        lista += e[0] + ", " 
    end
    lista = lista.chomp(", ")  
    "Twoje zapisane grupy to: #{lista}"
end

def grupa(tag)
    lista = ""
    for e in $database_group[tag]
        lista += e + ", "
    end
    lista = lista.chomp(", ")  
    "Członkowie grupy <#{tag}> to #{lista}"
end

#Przetwarzanie bazy danych
$database = {}
# Rekordy typu { nazwa => [numer, [lista tagów] ] }
$database_group = {}
# Rekordy typu { nazwa_grupy => [set z nazwami] }
File.open("C:/Users/Patryk/Desktop/data.txt", "r") do |f|
   f.each_line do |line|
      linia = line.split(';')
      nazwa = linia[0]
      numer = linia[1]
      tagi = linia[2].chomp.split(',')
      $database[nazwa] = [numer] + [tagi]
      for tag in tagi
        if $database_group[tag] 
           $database_group[tag] = $database_group[tag].add(nazwa)
        else
           $database_group[tag] = Set.new()
           $database_group[tag] = $database_group[tag].add(nazwa)
        end
      end
   end
end

#"Menu"
print "--------------------------------------------------------------------\n"
print "Załadowano program notatnik, wszystkie dane pobrano z pliku data.txt\n\n"
print "Dostępne polecenia to:\n-dodaj\n-znajdz (nazwa rekordu)\n-wypisz\n-grupa (nazwa grupy)\n"
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