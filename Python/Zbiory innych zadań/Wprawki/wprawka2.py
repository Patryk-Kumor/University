# -*- coding: cp1250 -*-

# lista p, wsp�czynniki wielomianu

x=int(input('Podaj punkt x: '))

def wielomian(x):
  w=0
  for i in P:
      w*=x
      w+=i
  return w
  

def surf(P,xs,xf,dx):
  pole=0 
  x=xs
  while x <= xf:
    malePole=wielomian(x)*dx
    pole+=malePole
    x=x+dx
  return pole
  

  

P=[]
n=int(input('Podaj najwy�sz� pot�g� wielomianu: '))
for i in range (n+1):
  m=int(input('Podaj '+ str(n+1-i) +'. wsp�czynnik: '))
  P.append(m)
print(P)
print('Warto�� wielomianu dla funkcji w punkcie x wynosi:',wielomian(x))

print()

xs=int(input('Podaj xs: '))
xf=int(input('Podaj xf: '))
dx=float(input('Podaj dx: '))

print('Pole to: ',surf(P,xs,xf,dx))


