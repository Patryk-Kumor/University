from math import *

def generator(n):
    tab=[]    
    for i in range(2,int(sqrt(n+1))):
        for j in tab:             
            if i % j == 0: break  
        else:   
            tab.append(i)            
    return tab
 

def rozklad(n):
    if n == 0:
        return []
    elif n == 1:
        return []
    else:
        tab = []
        primes = generator(n)
        i = 0

        while i < len(primes):
            if n % primes[i] == 0:
                tab.append(primes[i])
                n = n/primes[i]
            else:
                i+=1
        #print(tab)
        tab = zlicz(tab)
        print (tab)


def zlicz(tab):
    i=0
    tab_fin = []
    while i != len(tab):    
        tab_fin.append( (tab[i], tab.count(tab[i])))
        tab = usun(tab,tab[i])
    return tab_fin

def usun(tab,el):
    while el in tab:
        tab.remove(el)
    return tab

rozklad(5)
rozklad(15)
rozklad(49)
rozklad(13)
rozklad(756)
rozklad(12)
rozklad(222)
