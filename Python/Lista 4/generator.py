from math import sqrt
from itertools import islice
import time




##----------------------------------------##

def is_prime(n):
    if n % 2 == 0 and n > 2: 
        return False
    for i in range(3, int(sqrt(n)) + 1, 2):
        if n % i == 0:
            return False
    return True

##----------------------------------------##

def czasomierz(n):
    string = "Czas wyliczony dla n =" + str(n) + " dla funkcji w wersji:"
    print(string)
    
    start = time.clock()
    pierwsze_skladana(n)
    elapsed = time.clock()
    elapsed = elapsed - start
    print ("\t Składanej: ", elapsed)

    start2 = time.clock()
    pierwsze_funkcyjna(n)
    elapsed2 = time.clock()
    elapsed2 = elapsed2 - start2
    print ("\t Funkcjyjnej: ", elapsed2)

    start3 = time.clock()
    pierwsze_iterowane(n)
    elapsed3 = time.clock()
    elapsed3 = elapsed3 - start3
    print ("\t Iterowanej: ", elapsed3)

    print(51*"-")



##----------------------------------------##

def pierwsze_skladana(n):
    niepierwsze = [j for i in range(2, int(sqrt(n)+1)) for j in range(i*2, n+1, i)]
    pierwsze = [i for i in range(2, n+1) if i not in niepierwsze]
    return pierwsze

##---##

def pierwsze_funkcyjna(n):
    return list(filter(lambda i: all(i%div for div in range(2,int(sqrt(i)+1))),range(2,n)))

def pierwsze_funkcyjna2(n):
    return list(filter(lambda x: len(list(filter(lambda y: (x%y == 0) and (x != y), range(2, int(sqrt(x)+1))))) == 0, list(range(2, n+1))))

##---##

class Primes:
    def __init__(self):
        self.licznik = 1
        self.tab=[]   

    def __next__(self):
        self.licznik += 1
        if is_prime(self.licznik):
            return self.licznik
        #else:
        #   return self.__next__

    def __iter__(self):
        return self

def pierwsze_iterowane(n):
    L = []
    for prime in islice(Primes(), n-1):
       if prime:
            L.append(prime)
    return L

##----------------------------------------##

czasomierz(100)
czasomierz(1000)
czasomierz(10000)
#czasomierz(50000)




#start = time.clock()
#for i in range(10000):
#    is_prime(i)
#elapsed = time.clock()
#elapsed = elapsed - start
#print ("\t pętla dla n=10000: ", elapsed)

#print ("\n")
#print(51*"-")
#print(pierwsze_iterowane(100))


