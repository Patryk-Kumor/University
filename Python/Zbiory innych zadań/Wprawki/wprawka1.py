# -*- coding: cp1250 -*-

# lista p, wsp�czynniki wielomianu

x=int(input('Podaj punkt x: '))
def lista(x):
  P=[]
  n=int(input('Podaj najwy�sz� pot�g� wielomianu: '))
  for i in range (n+1):
    m=int(input('Podaj '+ str(n+1-i) +'. wsp�czynnik: '))
    P.append(m)
  print(P)
  
  w=0
  for i in range (n):
     w= w+ P[i]*x**(n-i) 
  w=w+P[-1]
  print('bezpo�rednio:',w)
  


  
  #i=0
  #while i<n
  #  w=w*[i]+P[i]
  #   
  # print('Hoh: ',w)
       
  
lista(x)
