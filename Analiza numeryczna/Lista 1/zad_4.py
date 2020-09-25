from math import *

# błąd 1/2*10^-6
# ln2 = 0.69314718056

def logarytm(x):
    k=1
    suma=0
    while True:
        suma += ( (-1)**(k-1) ) * ( (x-1)**k ) / k
        print("(k = ",k,") ln (", x, ") = ", suma)
        k+=1

        
def logarytm2(x):
    k=1
    suma=0
    while k < 2000000:
        suma += ( (-1)**(k-1) ) * ( ( x-1 )**k ) / k
        k+=1
    return (suma)


    
def logarytm_v2(x):
    x = x/e
    k=1
    suma=1
    while k < 500000:
        suma += ( (-1)**(k-1) ) * ( ( x-1 )**k ) / k
        k+=1
    return (suma)

def logarytm_v2(x):
    x = x/e
    k=1
    suma=1
    while k < 1000:
        a = ( (-1)**(k-1) ) * ( ( x-1 )**k ) / k
        suma += a
        k+=1
        print("k =",k, " Suma: ",  suma, "ax=",a)
    return (suma)




import random
import time

 
if __name__ == "__main__":
  start = time.clock()
  print(logarytm2(2))
  end = time.clock()
  total = end - start
  print("{0:02f}s".format(total))
  
  start = time.clock()
  print(logarytm_v2(2))
  end = time.clock()
  total = end - start
  print("{0:02f}s".format(total))

  start = time.clock()
  print(log(2))
  end = time.clock()
  total = end - start
  print("{0:02f}s".format(total))


  print("\n\n\n")
  for i in range(2,10):
      start = time.clock()
      print(logarytm_v2(i))
      end = time.clock()
      total = end - start
      print("{0:02f}s".format(total))
      print("---")
      start = time.clock()
      print(log(i))
      end = time.clock()
      total = end - start
      print("{0:02f}s".format(total))
      print("\n")
  




