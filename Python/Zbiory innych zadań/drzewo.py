from turtle import *
import random
tracer(4,0)
degrees(fullcircle=360.0)
SX=0
SY=0

def wróć(X):
    pu()
    goto(X)
    pd()
    
def drzewo(dl,Y):
    if dl==0:
        wróć(Y)
    else: 
        X=position()
        L=random.randint(0,45)
        lt(L)
        fd(dl)
        drzewo(int(dl-5),X)
        rt(L)
        wróć(X)
        R=random.randint(0,45)
        rt(R)
        fd(dl)
        drzewo(int(dl-5),X)
        lt(R)
        wróć(X)
        
lt(90)
fd(50)
drzewo(40,0)

