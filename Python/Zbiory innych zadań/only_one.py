def moje_only_one(L):
  L.sort()
  if L == []:
    return []
  if len(L)==2:
    if L[0]==L[1]:
      return [L[0]]
    else:
      return L
  R=[]
  if L == []:
    return []
  else:
    R.append(L[0])
  i=0
  j=1
  while j<len(L):
    if L[i]==L[j]:
      i=j
      j+=1
    else:
      R.append(L[j])
      i+=1
      j+=1
  return R
  
      

print(moje_only_one([1,22,3,1,5,1,8,1,4,6,2,5,3,1,4,6,2,5,32,3,1,5,1,8,1,4,6,2,5,3,4,4,5]))
print(moje_only_one([2,1]))
print(moje_only_one([1]))
A = list(range(1000000))
print (len(moje_only_one(A)))
