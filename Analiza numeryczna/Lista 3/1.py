from math import *
def silnia(n):  
    if n<2: 
        return 1
    else:
        for i in range(2,n):
            n*=i
        return n


    
def zad1_1(x):
    return e**(x**5)-e**(-7*(x**2))

def zad1_1_v2(x):
    if x < 1:
        sum = 0
        n = 1
        while n <= 150:
            sum += (x**5 + 7*(x**2))**n / factorial(n)
            n += 1
        return e**(-7*(x**2))*sum

    
def zad1_2(x):
    return atan(x)/x

def zad1_2_v2(x):
    sum = 0
    n = 0
    while n <= 1000:
        sum += ((-1)**n) * (x**(2*x+1)) / (2*n+1)  
        n += 1
    return sum


print(zad1_1(10**-32))
print(zad1_1_v2(10**-32))

print("----------------")

print(zad1_2(10**-32))
print(zad1_2_v2(10**-32))
