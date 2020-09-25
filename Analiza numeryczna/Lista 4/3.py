from math import *

def bisect(f, a, b, ep): #Liczy wartość z podanym epsilonem
 if (f(a)>0 and f(b)>0) or (f(a)<0 and f(b)<0):
  return 'Liczby(wartości) nie są przeciwnych znaków'
 else:  
    while True:
        x = (a+b)/2
        if(abs(a-b) < ep):
            return x
        else:
            if f(x)*f(a) > 0:
                a=x
            else:
                b=x
                
def bisect2(f, a, b, n): #Wykonuje n iteracji
 if (f(a)>0 and f(b)>0) or (f(a)<0 and f(b)<0):
  return 'Liczby(wartości) nie są przeciwnych znaków'
 else:
    i=0
    while i != n:
        x = (a+b)/2
        if f(x)*f(a) > 0:
            a=x
        else:
            b=x
        i += 1
    return (x)

def f(x):
    return x * e**(-x) - 0.06064

def co(oszacowanie,blad):
    if oszacowanie > blad:
        print("\toszacowanie jest większe")
    else:
        print("\trzeczywisty błąd jest większy")

##--------------------------------------------##    

Lep = []
Lreal=[]
for n in range(1,16):
    ep = (1) * 2**(-n-1)
    Lep.append(ep)
    x=bisect2(f,0,1,n)
    print(x)
    print("  n =", n)
    print("  oszacowanie błędu =", ep)
    blad = abs(0.0646926359947960-x)
    Lreal.append(blad)
    print("  rzeczywisty błąd = ", blad)
    co(ep,blad)
    print()

for i in range(len(Lep)-1): #Czy każdy kolejny wyraz jest mniejszy
    print(Lep[i] > Lep[i+1]) # szacowany
print("---")
for i in range(len(Lreal)-1): #rzeczywisty
    print(Lreal[i] > Lreal[i+1])

