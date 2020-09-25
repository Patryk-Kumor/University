from math import *


# błąd 0.0000001 = 10^-7
# pi = 3.14159265359

def szereg(): 
    suma=0
    k=0
    while True:
        suma += ((-1)**k) / (2*k + 1)
        k+=1
        print("(k = ",k,") pi = ", 4*suma)
        
def szereg2():
    suma=0
    k=0
    while k < 5000000:
        suma += ((-1)**k) / (2*k + 1)
        k+=1
    print("(k = ",k,") pi = ", 4*suma)
    while True:
        suma += ((-1)**k) / (2*k + 1)
        k+=1
        print("(k = ",k,") pi = ", 4*suma)

def szereg(n):
    suma=0
    k=0
    while k != n:
        suma += ((-1)**k) / (2*k + 1)
        k+=1
    return 4*suma
