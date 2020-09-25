from math import*


def licz(x, k):
    suma = 0
    for i in range (1,k):
        suma += (-1) ** (i-1) * (((x-1) ** i) / i)
    return suma

def log_v2(x):
    if x > 1 :
        s = x / e
        return 1 + 1 + log_v2(s/e)
    else:
        return 1 + licz((x/e),100)
    
import random
import time





print("\n\n\n")
for i in range(2,25):
      start = time.clock()
      print(log_v2(i))
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
