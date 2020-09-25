from math import *

def wielo(q,r):
    x = (r+sqrt(q**3 + r**2))**(1/3)
    x += (r-sqrt(q**3 + r**2))**(1/3)
    print(x)
    print()

def wielo2(q,r):
    p = (r + sqrt(q**3+r**2))**(2/3)
    w = 2*r*p/(p**2+p*q+q**2)
    print(w)
    print()



wielo(10**12,1)
wielo2(10**12,1)
print("---")

wielo(1, 10e-22)
wielo2(1, 10e-22)
print("---")

wielo(1, 10**22)
wielo2(1, 10**22)
print("---")

wielo(1, 1)
wielo2(1, 1)
print("---")

wielo(10**13, 1)
wielo2(10**13, 1)
print("---")
