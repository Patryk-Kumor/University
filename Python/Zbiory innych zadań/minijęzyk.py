from turtle import *
speed('fastest')
BOK = 10

#kolory = ['blue', 'red', 'green', 'pink', 'orange', 'yellow', 'khaki', 'black', 'brown']
kolory=[(0,0,1),(0.5,1,0),(1,1,0),(0,0,0)]

def kwadrat(BOK, kolor):
  fillcolor(kolor)
  begin_fill()
  for i in range(4):
    fd(BOK)
    rt(90)
  end_fill()
  
    
def murek(prog):
  k=kolor
  pk=k
  for x in prog:
    if x == 'f':
      kwadrat(BOK, k)
      fd(BOK)
    elif x == 'r':
      rt(90)
      fd(BOK)
    elif x == 'l':
      bk(BOK)
      lt(90)
    elif x == 'b':
      bk(BOK)
    elif int(x) in range(len(kolory)):
      pk=k
      k=kolory[int(x)]

murek('0ffff1')

