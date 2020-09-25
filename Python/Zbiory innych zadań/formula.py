def spelnialna_old(F):
  zmienne = set(F) - set("() !+*")
  F = F.replace('+', ' or ')
  F = F.replace('*', ' and ')
  F = F.replace('!', ' not ')
  return  any( eval(F,wart) for wart in wartosciowania(zmienne))

def spelnialna(F):
  
  G = F
  zmienne =  G.replace('(', ' ').replace(')', ' ').replace('+', ' ').replace('*', ' ').replace('!', ' ').split()
  F = F.replace('+', ' or ')
  F = F.replace('*', ' and ')
  F = F.replace('!', ' not ')
  return  any( eval(F,wart) for wart in wartosciowania(zmienne))

def tautologia(F):
  G = F
  zmienne =  G.replace('(', ' ').replace(')', ' ').replace('+', ' ').replace('*', ' ').replace('!', ' ').split()
  F = F.replace('+', ' or ')
  F = F.replace('*', ' and ')
  F = F.replace('!', ' not ')
  return  all( eval(F,wart) for wart in wartosciowania(zmienne))

def dict_add(D, k, v):
  D = dict(D)
  D[k] = v
  return D
      
def wartosciowania(Z):
  if len(Z) == 0:
    return [ {} ]
  Z = list(Z)  
  z = Z[0]
  Ws = wartosciowania(Z[1:])
  return [ dict_add(d, z, val) for d in Ws for val in [False, True] ]
  
print (wartosciowania('abc'))
print()
print(spelnialna('False'))
print()
print (tautologia('True'))
