def rev(słowo):
  return słowo[::-1]

def licznik_liter(x):
  słowo=str(x)
  S={}
  for element in słowo:
    if element in S:
      S[element]=S[element]+1
    else:
      S[element]=1
  return S
  
def sprawdź(coś_do_sprawdzenia,txt):
  txt=set(txt)
  
  X=licznik_liter(coś_do_sprawdzenia)
  W=set()
  print (txt)
  
  for słowo in txt:
    
    if len(str(coś_do_sprawdzenia))>len(słowo):
      print(słowo,' NIE')
    else: #SPRAWDZANIE CZY DA SIĘ W 'SŁOWO'
      Y=licznik_liter(słowo)
      for litera in coś_do_sprawdzenia:     
        if str(litera) in Y:
          if X[litera] > Y[litera]:
            break
          else:
            
            W.add(słowo) 
        else:
          pass
          
  print(W)
      
        

txt=open('slowa.txt', encoding='utf8').read().split()
txt=set(txt)

D=['okoń','pies', 'krowa', 'okolica','koń']
sprawdź('oko',D)

  
