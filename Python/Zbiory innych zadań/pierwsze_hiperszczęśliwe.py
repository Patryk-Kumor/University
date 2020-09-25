from math import sqrt
primes_under_1000=[2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131,
137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311,
313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503,
509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 643, 659, 661, 673, 677, 683, 691, 701, 709, 719,
727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
947, 953, 967, 971, 977, 983, 991, 997]
def pierwsza(n):
    if n <= 1000:
        return n in primes_under_1000
    if n % 2 == 0 or n % 3 == 0:
        return False

    for f in range(5, int(n ** .5), 6):
        if n % f == 0 or n % (f + 2) == 0:
            return 0
    return 1
#def pierwsza(n):   
 #   for j in range(2, int(sqrt(n)+1)):
  #          if n % j == 0:
   #             return 0                 
    #        else:
     #           return 1

def generator(ile):
    y=set()
    for i in range (100,1000):     #3$+''
        liczba = str(i) + ile*'7'
        print(liczba)
        if pierwsza(int(liczba)) == 1:
            y.add(int(liczba))
    for i in range (10,100):        #2$+''+1
        liczba = str(i) + ile*'7'
        for i in [1,3,5,7,9]:
            print(liczba+str(i))
            if pierwsza(int(liczba+str(i))) == 1:
                y.add(int(liczba+str(i)))
    for i in range (1,10):        #1$+''++1$+1
        liczba = str(i) + ile*'7'
        for i in range(0,10): #dodawanie 1$
            for j in [1,3,5,7,9]: #dodawanie +1
                print(liczba+str(i)+str(j))
                if pierwsza(int(liczba+str(i)+str(j))) == 1:
                    y.add(int(liczba+str(i)+str(j)))
    for i in range(10):
        liczba=ile*'7'+'0'
        for j in range(10):
          for k in [1,3,5,7,9]:
                print(liczba+str(j)+str(k))
                if pierwsza(int(liczba+str(j)+str(k))) == 1:
                    y.add(int(liczba+str(j)+str(k)))
    for i in range (10,100):     #''+3
        liczba = ile*'7' + str(i)
        for j in [1,3,5,7,9]:
            print(liczba+str(j))
            if pierwsza(int(liczba+str(j))) == 1:
                y.add(int(liczba+str(j)))
    print(len(y))

generator(7)
