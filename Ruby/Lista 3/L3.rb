require "prime"

### ZADANIE 2 - liczby pierwsze ###
def pierwsza(n)
    tab = [2]
    for i in 2...n
        for el in tab
            if (i % el == 0) then break
            elsif (i % el != 0) and (tab[tab.length-1]==el) then tab.push(i)
            end
        end
    end
    if n>=2 then tab else [] end
end

def pierwsza2(n)
    tab = [2]
    ((2..n).to_a).each {|i| tab.each {|el| break if (i % el == 0); tab.push(i) if ((i % el != 0) and (tab[tab.length-1]==el)) } }
    return tab
end

def primes(n)
    return Prime.take_while { |p| (p<n)}
end

### ZADANIE 2 - liczby doskonałe
def doskonale(n)
    tab = []
    sum = 0; x = 0
    for i in 0...n
        sum += 2**i
        if Prime.prime?(sum) 
            x=sum*(2**i)
            return tab if x >= n
            tab.push(x)
        end     
    end
    tab
end

def doskonale2(n)
    tab = []; sum = 0; x = 0
    ((0..n).to_a).each {|i| sum += 2**i;  if Prime.prime?(sum) then x=sum*(2**i); return tab if x >= n; tab.push(x) end}
    tab
end

### ZADANIE 3 - rozkład ###
def rozklad(n)
    if (n == 0) or (n == 1) then []
    else
        tab = []; prim = Prime.take_while {|p| p < n }; i=0
        while i < prim.length
            if n % prim[i] == 0
                tab += [prim[i]]; n = n/prim[i]
            else
                i += 1
            end
        end   
    end
    zlicz(tab)
end

def zlicz(tab)
    dic = {}; tab.each {|el| if !(dic[el]) then dic[el]=1 else dic[el]+=1 end}
    tab = []; dic.each {|el| tab.push(el) }; tab
end

### ZADANIE 3 - liczby zaprzyjaznione ###

def zaprzyjaznione(n)
    tab = []; (1..n).to_a.each {|x| a = suma_dzielnikow(x); b = suma_dzielnikow(a); tab.push([a,b].sort()) if  (x == b) and (x!=a)}; tab.uniq
end

def suma_dzielnikow(n)
    sum = 0; (1..n-1).to_a.each {|i| sum+=i if n%i==0}; sum
end

### TESTY ####

print pierwsza(100), "\n"
print pierwsza2(100), "\n"
print primes(100), "\n\n"

print doskonale(1000), "\n"
print doskonale2(1000), "\n\n"

print rozklad(1024), "\n"
print rozklad(756), "\n"
print rozklad(1025), "\n\n"

print zaprzyjaznione(1300), "\n"