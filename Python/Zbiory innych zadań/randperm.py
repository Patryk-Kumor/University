from random import *

def randperm(n):
    L=[]
    j=0
    while j<n:
        L.append(j)
        j+=1
     
    i=len(L)
    perm=[]
    while i > 0:
        x=randint(0,i-1)
        perm.append(L[x])
        del L[x]
        i=i-1   
    print(perm)
    

n=int(input("podaj n: "))
m=int(input("podaj ilość permutacji n: "))

for i in range(m):   
    randperm(n)
