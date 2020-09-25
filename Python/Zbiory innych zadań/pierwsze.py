from math import sqrt

def pierwsze(max):
    P=[]
    for i in range(2,max+1):
        
        for j in P:
            if i % j == 0: break
        else:
            yield i              
            P.append(i)
            
            #if L.count('777') == 1:
            #    print (L)
            
        
            

input('Rozpocznij: ')
n = 0
for i in pierwsze(100000):
    L = str(i)

    if L.count('777') == 1:
        print (L)
        n=n+1
print('Szczęśliwych liczb jest: ',n)
