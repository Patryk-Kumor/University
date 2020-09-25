def statystyka_slow(nazwa_pliku)
    database = {}
    liczba = 0
    File.open(nazwa_pliku, "r:UTF-8") do |f|
        f.each_line do |line|
            line = line.downcase.gsub(/[^a-zA-Z0-9-zżźćńółęąśŻŹĆĄŚĘŁÓŃ_']/, " ") 
            line = line.split(' ')
            for e in line
                liczba += 1
                if database[e]
                    database[e] += 1
                else
                    database[e] = 1
                end
            end
        end
     end
     for element in database
        database[element[0]] = element[1] / liczba.to_f
     end
     database
end
puts statystyka_slow("C:/Users/Patryk/Desktop/tekst.txt")
print "\n\n"
puts statystyka_slow("C:/Users/Patryk/Desktop/makbet.txt")