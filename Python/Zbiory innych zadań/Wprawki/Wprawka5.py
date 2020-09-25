from turtle import *
from math import sin,pi

tracer(0,1)
global SX
global SY
SX=0
SY=0
BOK=2
colormode(255)
e=0.5


P=[8,0,-12,0]   
def wart_wielomian(x,P):
  w=0
  for i in P:
      w*=x
      w+=i
  return w

def f(x):   #Np.Duży sinus
   y=sin(x*pi/180)*200
   return y
  
def w(x):  #Wielomian
   y=wart_wielomian(x,P)
   return y
  
def kwadrat(BOK,SX,SY):
  fillcolor('black')
  pu()
  goto(SX, SY)
  pd()
  begin_fill()
  for i in range(4):
    fd(BOK)
    rt(90)
  end_fill()


#Okienko chyba: od -450 do 450, plus minus
  
def plot(f, xs, xf):
  SX=xs
  while SX <= xf:
    SX=SX+e
    SY=f(SX)
    kwadrat(2,SX,SY)
    

plot(f, -200, 200)
#plot(w, -200, 200)

