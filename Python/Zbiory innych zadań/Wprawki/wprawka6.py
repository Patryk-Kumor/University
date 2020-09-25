def permi(xs):
  Z = []
  
  if len(xs) == 0:
    print ('[[]]')
    return [[]]
  
  else:
    S = permi(xs[1:])
    for el in S:
      for i in range(len(el)+1):
        X=el
        print(i)
        X[i:i]=xs[0:1]
        print(X)
        Z.append(X)
        
      
  print(Z)
  return Z
      
permi([1,2,3])  
      
      
