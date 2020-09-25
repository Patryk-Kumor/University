import turtle
from random import randint
from turtle import fd, rt, lt, bk, speed, pu, pd, pensize

speed('fastest')




def slupek():
    x=(int(randint(10,300)))
    fd(10)
    lt(90)
    fd(x)
    lt(90)
    fd(10)
    lt(90)
    fd(x)
    lt(90)
    fd(10)
    pu()
    fd(5)
    pd()
    
for i in range(randint(10,40)):
    slupek()
