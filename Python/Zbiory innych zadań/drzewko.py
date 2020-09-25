from turtle import *
from random import *
lt(90)
pu()
bk(250)
pd()
speed(0)
def drzewko(l,a):
    tracer(100)
    if l < 2:
        return
    fd(l)
    rt(a)
    x=uniform(0.60, 0.95)
    y=uniform(0.8, 1.2)
    drzewko(l*x,a*y)
    lt(a*2)
    x=uniform(0.60, 0.95)
    y=uniform(0.8, 1.6)
    drzewko(l*x, a*y)
    rt(a)
    bk(l)
    return

drzewko(50,20)
input()
