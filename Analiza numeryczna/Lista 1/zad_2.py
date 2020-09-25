from math import *


def ciag_rek(x):
    if x == 0:
        return 1
    if x == 1:
        return 1/5
    else:
        return 26/5 * ciag_rek(x-1) - ciag_rek(x-2)

    
def ciag(n): #Zepsuje coś koło +-20
    x1=1
    x2=1/5
    print( "x 1 = 1" )
    print( "x 2 = 1/5" )
    for i in range(n-2):
            x3 = 26/5*x2 - x1
            print( "x",i+3, " = ", x3 )
            x1 = x2
            x2 = x3


def ciag2(n): #Lepiej
    for i in range(n):
        print("ciąg(",i,") = ",(1/5)**i)
