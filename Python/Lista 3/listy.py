from math import *
import time
from functools import *

def timer():
    start = time.clock()
    pierwsze_skladana(10000)
    elapsed = time.clock()
    elapsed = elapsed - start
    print ("Time spent in (skladana) is: ", elapsed)
    start = time.clock()
    pierwsze_funkcyjna2(10000)
    elapsed = time.clock()
    elapsed = elapsed - start
    print ("Time spent in (funkcyjna) is: ", elapsed)


def timer2():
    start = time.clock()
    doskonale_skladana(8129)
    elapsed = time.clock()
    elapsed = elapsed - start
    print ("Time spent in (skladana) is: ", elapsed)
    start = time.clock()
    doskonale_funkcyjna(8129)
    elapsed = time.clock()
    elapsed = elapsed - start
    print ("Time spent in (funkcyjna) is: ", elapsed)


##----------------------------------------##


def pierwsze_skladana(n):
    niepierwsze = [j for i in range(2, int(sqrt(n)+1)) for j in range(i*2, n+1, i)]
    pierwsze = [i for i in range(2, n+1) if i not in niepierwsze]
    return pierwsze

#

def pierwsze_funkcyjna(n):
    return list(filter(lambda x: len(list(filter(lambda y: (x%y==0) and (x!=y), range(2, int(sqrt(x)+1))))) == 0, list(range(2, n+1))))


def pierwsze_funkcyjna2(n):
    return list(filter(lambda i: all(i%div for div in range(2,int(sqrt(i)+1))),range(2,n)))





def is_prime(n):
    if n % 2 == 0 and n > 2: 
        return False
    for i in range(3, int(sqrt(n)) + 1, 2):
        if n % i == 0:
            return False
    return True


##----------------------------------------##


def doskonale_skladana(n):
    return [i for i in range(2,n+1) if sum([j for j in range (1,i//2+1) if i%j==0]) == i]

#

def doskonale_funkcyjna(n):
    return list(filter(lambda x : x == reduce(lambda a,b: (a+b), filter(lambda d : x%d==0, range(1,x//2+1))), range(2,n+1)))


def doskonale_funkcyjna2(n):
    return list(filter(lambda x:  sum (i for i  in range(1,int(x/2)+1) if x%i==0) == x , range(2,n)))    


def doskonale_funkcyjna3(n):
    return list(filter(lambda x:  is_perf(x), range(2,n)))  


def is_perf(n):
    return sum(i for i  in range(1,int(x/2)+1) if x%i==0)==x


##----------------------------------------##



timer()
print("---")
primes = pierwsze_skladana(100)
print (primes)
#for i in primes:
#        print (is_prime(i))
print("---")
primes = pierwsze_funkcyjna(100)
print (primes)
print("---")
primes = pierwsze_funkcyjna2(100)
print (primes)
#for i in primes:
#        print (is_prime(i))
print("---")
timer2()
print("---")
print(doskonale_skladana(8129))
print("---")
print(doskonale_funkcyjna(8129))
print("---")
print(doskonale_funkcyjna2(8129))
print("---")
print(doskonale_funkcyjna3(8129))
