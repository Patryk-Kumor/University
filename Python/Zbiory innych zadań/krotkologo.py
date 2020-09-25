from turtle import *

P= [ ( 'repeat',10, [('fd',50),('repeat', 4, [('fd',40), ('rt',90)]),('bk',50),('lt',36)] ) ]
L= ('fd',36)

zbiór={'fd','bk','rt','lt'}

def wykonaj(P):
    s=P[0]
    n=P[1]
    if s=='fd':
        fd(n)
    if s=='bk':
        bk(n)
    if s=='rt':
        rt(n)
    if s=='lt':
        lt(n)
        
def wykonaj2(P):
    
wykonaj(L)
