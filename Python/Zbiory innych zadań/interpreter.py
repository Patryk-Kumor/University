from turtle import *
from math import fabs
tracer(4,1)
BOK = 10
global pozycja
global ile
global k1
global k2
global start

#kolory=['blue','green','yellow','black'] od 0 do 3
kolory=[(0,0,1),(0,1,0),(1,0,1),(0,0,0),(0.5,0.5,0.5)]

def kwadrat(BOK, kolor):
  fillcolor(kolor)
  begin_fill()
  for i in range(4):
    fd(BOK)
    rt(90)
  end_fill()  
 
def mieszanina(k1,k2,a):
  r1 = k1[0]
  g1 = k1[1]
  b1 = k1[2]
  r2,g2,b2 = k2
  r3 = (1-a) * r1 + a * r2
  g3 = (1-a) * g1 + a * g2
  b3 = (1-a) * b1 + a * b2
  return (fabs(r3),fabs(g3),fabs(b3))

def zlicz(start, napis):
  L=list(napis)
  i=start
  ile=0
  if start == len(L):
    print ('koniec')
  if L[0]=='0' or L[0]== '1' or L[0]=='2' or L[0]=='3'or L[0]=='4':
    for x in L[i+1:len(L)]:
      if x=='f':
        ile+=1
        start+=1
      elif x=='r' or x=='l':
        start+=1
      elif x=='0' or x== '1' or x=='2' or x=='3' or x=='4':
        start+=1
        return [start,ile,x]
        break

def murek(napis):
  global pozycja
  global ile
  global k1
  global k2
  global start

  pozycja=0
  start=0
  
  for x in napis:
    print(x)
    if start==len(napis):
      break
    elif x=='0' or x=='1' or x=='2' or x=='3'or x=='4':    #+uwzględnić ostatnie liczby. Estetyka
      
      k1=(kolory[int(x)])
      print('kolor1 to',k1)
    
      k2=(kolory[int( zlicz(start,napis)[2] )])
      print('kolor2 to',k2)

      ile=int( zlicz(start,napis)[1] )
      start=int( zlicz(start,napis)[0] )

      pozycja=0
         
    elif x == 'f':
      a = pozycja / ile
      print(pozycja)
      print(ile)
      print(a)
      kwadrat(BOK, mieszanina(k1,k2,a) )
      fd(BOK)
      pozycja+=1
    elif x == 'r':
      rt(90)
      fd(BOK)
    elif x == 'l':
      bk(BOK)
      lt(90)
  
murek('0fffffrfffffrffffrffff1rfffrfffrffrffrfrf3')
