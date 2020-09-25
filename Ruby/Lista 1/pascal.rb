def wypisz(tab)
    print tab.join(' ') + "\n"
end

def pascal(n)
    tab1 = [1]
    tab2 = [1,1]
    if n==1 
        wypisz (tab1)
    else n==2
        wypisz (tab1)
        wypisz (tab2)
        i = 3
        while (i <= n)
            tab3 = [1] + tab1 + [1]
            for j in 1..(tab3.length-2) 
              tab3[j] = tab2[j-1] + tab2[j]
            end 
            wypisz(tab3)
            i += 1 
            tab1=tab2
            tab2=tab3
        end
    end
end

for i in 1..10
    pascal (i)
    print "\n---\n\n"
end

num = gets.chomp