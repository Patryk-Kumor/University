def wart_wielomian(x,P):
  w=0
  for i in P:
      w*=x
      w+=i
  return w

def f(x):
    y=wart_wielomian(x,P)
    return y

def bisect(f, x, y):
 if (f(x)>0 and f(y)>0) or (f(x)<0 and f(y)<0):
  return 'Liczby(wartości) nie są przeciwnych znaków'
 else:  
    e=2**(-32)
    while True:
        c = (x+y)/2
        if(abs(x-y) < e):
            return c
        else:
            if f(c)*f(x) > 0:
                x=c
            else:
                y=c



P=[1, 0, 0, -4, -8] #wielomian x^4-4x-8


bi=bisect(f, -1, 3)
print('Miejsce zerowe to:',bi)


