from math import *


def pierwiastki(a,b,c):
    print("-Wersja 1:-")
    d=(b*b-4*a*c)
    if d > 0:
        print("x1 = ", (  -b + sqrt(d) ) / (2*a)   )
        print("x2 = ", (  -b - sqrt(d) ) / (2*a)   )
    elif d==0:
        print("x = ",  (  -b + sqrt(d) ) / (2*a)   )
    else:
        print ("delta ujemna")
    print("---\n")

def pierwiastki_v2(a,b,c):
    print("-Wersja v2:-")
    d=(b*b-4*a*c)
    
    if d > 0:
        if b>0:
            x = (-b - sqrt(d))/(2*a)
            print("x1 = ", x)
            print("x2 = ", (c/(a*x)) )
        else:
            x = (-b + sqrt(d))/(2*a)
            print("x1 = ", x)
            print("x2 = ", (c/(a*x)) )
            
    elif d==0:
        print("x = ",-b/2*a)
    else:
        print ("delta ujemna")
    print("\n---------\n")

pierwiastki(1,-2,1)
pierwiastki_v2(1,-2,1)

pierwiastki(1,2**128,-2)
pierwiastki_v2(1,2**128,-2)

pierwiastki(1,-2**32,1)
pierwiastki_v2(1,-2**32,1)

pierwiastki(9.0,  20 ** 9,   1.0)
pierwiastki_v2(9.0,  20 ** 9,   1.0)

pierwiastki(1,    80,      1.0e-13)
pierwiastki_v2(1,    80,      1.0e-13)

pierwiastki(1.12345e-12,   1,   1.01e-90  )
pierwiastki_v2(1.12345e-12,   1,   1.01e-90  )

pierwiastki(1.12345e-12,   121212,  1.010001)
pierwiastki_v2(1.12345e-12,   121212,  1.010001)

pierwiastki(1.123e-12,   12 ** 64, 1234213)
pierwiastki_v2(1.123e-12,   12 ** 64, 1234213)

pierwiastki(1111999211231139, 12 ** 64, 1234213)
pierwiastki_v2(1111999211231139, 12 ** 64, 1234213)
