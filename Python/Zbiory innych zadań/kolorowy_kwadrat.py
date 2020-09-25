from turtle import *
import random

tracer(4,0)


def kwadraty(bok):
    fillcolor((random.random(),random.random(), random.random()))
    begin_fill()
    for i in range(4):
        fd(bok)
        lt(90)
    end_fill()
    pu()
    fd(bok)
    pd()

def czesc_kwadrat(n):
    for i in range(n):
        kwadraty(bok)

def wielki_kwadrat(n):
    for i in range(n):
        czesc_kwadrat(n)
        pu()
        home()
        lt(90)
        fd(bok+i*bok)
        rt(90)
        pd()
        
               
bok=20
wielki_kwadrat(5)

x=int(input('Podaj ilość małych kwadratów do następnego rysunku: '))

home()
clear()
wielki_kwadrat(x)


