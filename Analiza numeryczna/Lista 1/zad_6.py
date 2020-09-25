from math import *



def ATan(x):
    return atan(x)

def Large_ATan(x):
    if x < 0:
        a = - pi/2
        return a - atan(1/x)
    else:
        a = pi/2
        return a - atan(1/x)


for i in range(-100,-1):
    print(atan(i))
    print(Large_ATan(i))
    print("---")
for i in range(1,100):
    print(atan(i))
    print(Large_ATan(i))
    print("---")
