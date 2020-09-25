from turtle import *

tracer(0,1)

def wypustka_mala(bok):
  fd(bok)
  lt(90)
  fd(bok-1/4*bok)
  rt(90)
  fd(bok)
  rt(90)
  fd(bok-1/4*bok)
  lt(90)
  fd(bok)

def wypustka_duza(bok):
  lt(90)
  wypustka_mala(bok-1/4*bok)
  rt(90)
  wypustka_mala(bok-1/4*bok)
  rt(90)
  wypustka_mala(bok-1/4*bok)
  
def book(bok):
  wypustka_mala(bok)
  wypustka_duza(bok)
  lt(90)
  wypustka_mala(bok)

def wiekszy_bok(bok):
  book(bok)
  lt(90)
  book(bok)
  rt(90)
  book(bok)
  rt(90)
  book(bok)
  lt(90)
  book(bok)

def caly(bok):
  for i in range(4):
    wiekszy_bok(bok)
    rt(90)

pu()
bk(120)
lt(90)
fd(120)
rt(90)
pd()
caly(10)
