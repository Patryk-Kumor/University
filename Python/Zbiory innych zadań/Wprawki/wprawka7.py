from math import pi
def cont_frac(num,den,k):
  w=1
  i=k
  while i!=-1:
    w=num(i)/(den(i)+w)
    i-=1
  return w

def jeden(i): #Pomocnicza funkcja zawracająca 1
  return 1
    
def euler1(i):  #|Pomocnicze #1 euler
  return 1

def euler2(x):  #|Pomocnicze #2 euler
  L=[1,2,1,1,4,1,1,8,1,1,16,1,1,32,1,1,64,1,1,128,1,1]
  return L[x]

def euler(x):   #|Pomocnicze #3 euler #Nie jest używana
  L=[]
  n=1
  while len(L)<x:
   if  len(L)!=x :
      L.append(1)
      L.append(1)
   if  len(L)!=x :
      L.append(2**n)
      n+=1
  return(L[x+1])



def tangens(x,k):
 def tangens1(i):
  if i==0:
    return x
  else:
    return (-1)*(x**2)
 def tangens2(x):  
  w=1
  for i in range(x):
    w=w+2
  return w
 return cont_frac(tangens1,tangens2,10)

print('1/(1+1/...):',cont_frac(jeden,jeden,4)) #den/num=1, nasze funkcje pomocnicze

print('euler: ',cont_frac(euler1,euler2,10)+2) #euler



print('tangens pi/4: ',(tangens(pi/4,10))) #tangens pi/4
#print('tangens 2pi/3=sqrt(3): ',(tangens(2*pi/3,10))) #tangens pi/4
