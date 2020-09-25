from turtle import *
from wdi import *
from duze_cyfry import *
from random import *

#Nasza tablica ma 5x5

BOK = 10
tracer(0,1)
SX = 0
SY = 0

def kwadrat(x, y, kolor):
  fillcolor(kolor)
  pu()
  goto(SX + x * BOK, SY + y * BOK)
  
  begin_fill()
  for i in range(4):
    fd(BOK)
    rt(90)
  end_fill()
  pd()

def Cyferka(N):
  Cyfry[N] = list(map(list, Cyfry[N]))
  rysuj(Cyfry[N])

M1=5
M2=5
T= Array(M1,M2)

#for i in range(M1):
 # for j in range(M2):  
  #  printf("T[%d][%d] == %d\n", i, j, T[i][j])

def rysuj(T):
  kolorek=(random(),random(),random())
  for y in range(len(T)):
    for x in range(len(T[y])):
      if T[y][x] == '#':
        kolor = kolorek
      else:
        kolor = 'white'
      kwadrat(x, y, kolor)
  update()
def rysowanie_liczby(liczba):
  global SX
  liczba=list(str(liczba))
  for element in liczba:
    x=element
    if element == '-':
      x=int(10)
    Cyferka(int(x))
    SX=SX+BOK*6
  SX=0
  


