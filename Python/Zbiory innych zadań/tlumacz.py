import random

#brown=open('brown.txt', encoding='utf8').read().split()
źródło=open('tekst.txt', encoding='cp1250').read().split()

#Popularność
dic={}
for x in open('brown.txt', encoding='utf8').read().split():
  if x in dic:
    dic[x]+=1
  else:
    dic[x]=1


def szukaj(słowo):
  X=[]
  for x in open('pol_ang.txt', encoding='utf8'):
    x = x[:-1]
    wiersz = x.split('=')
    if len(wiersz) != 2:
      continue
    pol,ang = wiersz
    if pol==słowo:
      X.append(ang)
  return random.choice(X)
      
    
  

pol_ang = {}
for x in open('pol_ang.txt', encoding='utf8'):
  x = x[:-1]
  wiersz = x.split('=')
  if len(wiersz) != 2:
    continue
  pol,ang = wiersz
  if pol in pol_ang:
   if ang in dic and pol_ang[pol] in dic: #jeśli nie ma w Brown 
    if dic[ang]>dic[pol_ang[pol]]:
      pol_ang[pol] = ang
    else:
      pass  
   else:
     if ang not in dic:
        pass
     if pol_ang[pol] not in dic:  
        pol_ang[pol] = ang 
  else:
    pol_ang[pol] = ang



def tlumacz(L):
  wynik = []
  for w in L:
    if w in pol_ang:
      if pol_ang[w] in wynik:  ##dwa razy musi być
        wynik.append(szukaj(w))
      else:
        wynik.append( pol_ang[w] )
    else:
      wynik.append('?' + w)
 
  return wynik
  
    
for wiersz in open('tekst.txt', encoding='cp1250'):
  wiersz = wiersz.split()
  print (' '.join(tlumacz(wiersz)))
