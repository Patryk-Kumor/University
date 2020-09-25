from math import *


def pierwiastki(a,b,c):
    d=(b*b-4*a*c)
    if d > 0:
        print("x1 = ", (  -b + sqrt(d) ) / (2*a)   )
        print("x2 = ", (  -b - sqrt(d) ) / (2*a)   )
    elif d==0:
        print("x = ",  (  -b + sqrt(d) ) / (2*a)   )
    else:
        print ("delta ujemna")
