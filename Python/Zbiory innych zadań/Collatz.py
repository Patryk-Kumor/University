from statistics  import median

def F(n):
    if n % 2 == 0:
        return  n / 2
    else:
        return 3 * n + 1

def energia(x):   
  i=0
  while True:
    #print(F(x))
    x=F(x)
    i+=1
    if x==1:
        #print('Koniec. Energia to:',i)
        break
  return i
    
def srednia(L):
   suma = 0
   for element in L:
      suma += element
   return suma/len(L)    

        

def analizaCollatza(a,b):
    L=[]
    for i in range(b-a+1):
        L.append(energia(a+i))
    print(L)
    print('Średnia: ',srednia(L))
    print('Maksimum: ',max(L))
    print('Minimum: ',min(L))
    print('Mediana: ',median(L))
    
x=int(input('Podaj x: '))
print('Energia x to: ',energia(x))
print()


a=int(input('Podaj a: '))
b=int(input('Podaj b: '))
analizaCollatza(a,b)

    
    
