def merge(xs,ys):
  R=[]
  i=0
  j=0
  lx=len(xs)
  ly=len(ys)
 # if xs[0]>=ys[0]:
 #    pass
 # else:
 #   zamiana=xs
 #   xs=ys
 #   ys=zamiana

  while i<lx or j<ly:
    if i>lx:
      R.append(ys)
    if j>ly:
      R.append(xs)
    if xs[i]<=ys[j]:
      R.append(xs[i])
      i+=1
    else:
      R.append(ys[j])
      j+=1
      
  return R

merge([1, 2, 5], [2, 4, 9])
merge([2, 4, 9],[1, 2, 5],)

