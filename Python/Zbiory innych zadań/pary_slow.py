import random

txt=open('slowa.txt', encoding='utf8').read().split()
txt=set(txt)


def wypisz(L):
  w=''
  for litera in L:
    w+=litera
  return w

def pary(K,L):
  W=[]
  for słowo in L:
    for drugie_słowo in L:
      if słowo==drugie_słowo or len(drugie_słowo)<2:
        pass
      else:
        układane=list(drugie_słowo)
        for i in range(len(układane)):
          if str(wypisz(układane[0:i])+słowo+wypisz(układane[i:-1])) in txt:
            W.append(str(słowo+' - '+drugie_słowo))
          else:
              pass
  print(W)

def pary2(K):
  L=random.sample(txt,K)
  print(L)
  W=[]
  for słowo in L:
    licznik=0
    while licznik!=K:
      drugie_słowo=str(random.sample(txt,1)[0])
      if słowo==drugie_słowo or len(drugie_słowo)<2:
        break
      else:
        układane=list(drugie_słowo)
        for i in range(len(układane)):
          if str(wypisz(układane[0:i])+słowo+wypisz(układane[i:-1])) in txt:
            W.append(str(słowo+' - '+drugie_słowo))
            licznik+=1
          else:
              break
  print(W)
 
L=['kotka', 'kula', 'kutwa', 'lin', 'matura', 'para', 'pranie', 'ropa', 'setka', 'sowa']
pary(1,L)
#pary2(10)
