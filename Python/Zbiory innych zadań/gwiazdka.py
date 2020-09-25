import turtle

from turtle import fd, rt, lt, bk, speed, pu, pd

speed('fastest')

def malaGwiazdka(ile, dl):
  for i in range(ile):
    fd(dl)
    rt(360//ile)
    bk(dl)
    

  
def gwiazdka(ile,dl):
  for i in range(ile):
    fd(dl)
    malaGwiazdka(9,40)
    bk(dl)
    rt(360//ile)
    
    


gwiazdka(10,100)

x=int(input('Podaj ilość: '))
y=int(input('podaj dlugość: '))

gwiazdka(x,y)
