from math import *

def bisect(f, a, b, ep): #Liczy wartość z podanym epsilonem
 if (f(a)>0 and f(b)>0) or (f(a)<0 and f(b)<0):
  return 'Liczby(wartości) nie są przeciwnych znaków'
 else:
    i=0
    while True:
        i += 1
        x = (a+b)/2
        if(abs(a-b) < ep):
            print(i)
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
        if abs(-0.759426-x)<=ep:
            print("iteracja:",i, "x1 True")
        if abs(0.184586-x)<=ep:
            print("iteracja:",i, "x2 True")
    return (x)

def f(x):
    return x**2 - 2*cos(3*x+1)


  
a = -0.759426
b = 0.184586

print("Wolfram: -0.759426")
print("          0.184586", "\n")

ep=10**(-5)
print("while |a-b|>e :")
x1 = bisect(f,-sqrt(2),0,ep)
x2 =  bisect(f,0,sqrt(2),ep)
print("\t",x1)
print("\t",x2)
print("\t","błąd =", abs(a-x1))
print("\t","błąd =", abs(b-x2))
print()

n=abs(ceil(log2(sqrt(2)/2*10**(-5))))
print("iteracja dla n =",n)
x1 = bisect2(f,-sqrt(2),0,n)
x2 =  bisect2(f,0,sqrt(2),n)
print("\t",x1)
print("\t",x2)
print("\t","błąd =", abs(a-x1))
print("\t","błąd =", abs(b-x2))
print()
