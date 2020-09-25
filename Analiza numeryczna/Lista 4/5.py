from math import *
#-----------------------------------------------------
# Funkcja, której miejsce zerowe obliczamy
def f(x):
 if x>0:
  return 1 / sqrt(x)
 else:
  return 0
#-----------------------------------------------------
# Oblicza pochodną funkcji f(x)
def fp(f,x,h):
  return (f(x+h)-f(x))/h
h = 10**(-10)
#-----------------------------------------------------
# Program główny




