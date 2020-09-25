# -*- coding: cp1250 -*-

# lista p, współczynniki wielomianu

x=int(input('Podaj punkt x: '))
def lista(x):
  P=[]
  n=int(input('Podaj najwyższą potęgę wielomianu: '))
  for i in range (n+1):
    m=int(input('Podaj '+ str(n+1-i) +'. współczynnik: '))
    P.append(m)
  print(P)
  
  w=0
  for i in range (n):
     w= w+ P[i]*x**(n-i) 
  w=w+P[-1]
  print('bezpośrednio:',w)
  


  
  #i=0
  #while i<n
  #  w=w*[i]+P[i]
  #   
  # print('Hoh: ',w)
       
  
lista(x)
