from turtle import *
tracer(0,1)
SX=0
SY=0
BOK=2
colormode(255)


txt=open('obraz.txt', encoding='utf8').readlines()

def krotka(słowo):
  kolorek=pixel
  kolorek=kolorek.strip("(")
  kolorek=kolorek.strip(")")
  L=kolorek.split(",")
  return (int(L[0]),int(L[1]),int(L[2]))
  
def kwadrat(kolor):
  fillcolor(kolor)
  pu()
  
  goto(SX, SY)
  begin_fill()
  for i in range(4):
    fd(BOK)
    rt(90)
  end_fill()
  pd()

  
for line in txt:
  L=line.split()
  for pixel in L:
    kwadrat(krotka(pixel))
    SX+=BOK
  SY-=BOK
  SX=0
    
