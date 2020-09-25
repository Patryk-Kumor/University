from decimal import Decimal, getcontext
import sys, codecs, locale, re
getcontext().prec=105
#Bailey–Borwein–Plouffe formula#
pi  =  str(sum(1/Decimal(16)**k *
          (Decimal(4)/(8*k+1) -
           Decimal(2)/(8*k+4) -
           Decimal(1)/(8*k+5) -
           Decimal(1)/(8*k+6)) for k in range(105)))
pi = list(str(pi))[:-4]
for i, cyfra in enumerate(pi):
    if cyfra=='0':
        pi[i] = '10'
del pi[1]
with open('robinson.txt', encoding='utf-8') as plik: 
    Slowa = [slowo for line in plik for slowo in re.split('\W+', line.strip())
             if slowo!='']

def szukaj_ciag(L):
    Najdluzszy_ciag = []
    najwiekszy_nr = 0
    dlug_listy = len(L)
    for i in range(dlug_listy):
        j = 0
        it = i
        aktualny_ciag = []
        while len(L[it])==int(pi[j]):
            aktualny_ciag.append(L[it])
            j+=1
            it+=1
            if it>=dlug_listy: break
            len(L[it])
        if j>najwiekszy_nr:
            Najdluzszy_ciag = aktualny_ciag
            najwiekszy_nr = j
    return Najdluzszy_ciag
print(szukaj_ciag(Slowa))

