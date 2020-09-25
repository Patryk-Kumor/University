from math import sqrt

i=10000000000
n=int(input('Podaj ilość 7: '))


def liczenie(i):
 ile=0
 while i>1000000000:
    P=str(i)
   # if P.count(n*'7'):
    if P.count('7777777'):
        for j in range(2, int(sqrt(i))):
            if i % j == 0:
                print (i, " dzieli się przez ", j)
                break    
            
        else:
            ile=ile+1
            print (i," jest największą hiperszczęśliwą liczbą pierwszą. To już ",ile, "taka liczba")  
    i=i-1

liczenie(i)           
#9977777773
