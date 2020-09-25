import random


zbiór=open('slowa.txt', encoding='utf8').read().split()
zbiór=set(zbiór)

def licznik(x):   #Zamiana na słownik (klucz litera: wartość ilość)
  słowo=str(x)  
  S={}
  for element in słowo:
    if element in S:
      S[element]=S[element]+1
    else:
      S[element]=1
  return S
def sprawdzarka1(słowo):
  x=1
  S=licznik(słowo)
  for litera in S:
    if S[litera]>1:
      x=0
  return x

txt=set()

for słowo in zbiór:
  if sprawdzarka1(słowo):
    txt.add(słowo)
print('Set gotowy')
    


def sprawdzarka(L):
  x=1
  słowa=''
  for i in L:
    słowa+=str(i)
  S=licznik(słowa)
  for litera in S:
    if S[litera]>1:
      x=0
  return x
    
def losuj(x):
  L=[]
  for i in range(x):
     x=random.sample(txt,1)[0]
     print('NASZ X: ', x)
     if sprawdzarka(L+[x])==1:
          L.append(x)
          print(L)
    
losuj(500)
