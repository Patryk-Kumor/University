import random


txt=open('slowa.txt', encoding='utf8').read().split()
txt=set(txt)

def słownik(txt):
  dic={}
  for słowo in txt:
    dic[słowo]=len(słowo)
  return dic

def para(słowo):
    L=[]
    zbiór=set(słowo)
    for wyraz in txt:
      if set(wyraz).issubset(zbiór) and len(wyraz)<len(słowo):
        L.append(wyraz)
    return(L)
  
def licznik(x):   #Zamiana na słownik (klucz litera: wartość ilość)
  słowo=str(x)  
  S={}
  for element in słowo:
    if element in S:
      S[element]=S[element]+1
    else:
      S[element]=1
  return S

def sprawdź(coś_do_sprawdzenia,słowo):
  X=licznik(coś_do_sprawdzenia)
  Y=licznik(słowo)
  if len(coś_do_sprawdzenia)<=len(słowo): 
    for słowo in X:
      for litera in coś_do_sprawdzenia:
        if str(litera) in Y:
          if X[litera] > Y[litera]:
             return False
        else:
          return False
    return True
  else:
    return False
  
def pary(słowo):
  X=imię_nazwisko
  Y=set()
  L=para(imię_nazwisko)
  for słowo in L:
    for drugie_słowo in L:
      if len(słowo+drugie_słowo)==len(X):
        if słowo==drugie_słowo:
          pass
        else:
          if sprawdź(X,(słowo+drugie_słowo)) is True:
            if drugie_słowo+' '+słowo in Y:
              pass
            else:
              print(słowo+' '+drugie_słowo)
              break
      else:
        pass
      
def SZUKANE(K):
  L=random.sample(txt,K)
  for słowo in L:
    pary(słowo)
SZUKANE(2)
