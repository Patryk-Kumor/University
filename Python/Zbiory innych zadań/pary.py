def rev(słowo):
  return słowo[::-1]



txt=open('slowa.txt', encoding='utf8').read().split()
txt=set(txt)

#for słowo in txt:
#  print(słowo)

W = set()


for słowo in txt:
  if rev(słowo) in txt:
    if rev(str(słowo)+'-'+rev(słowo)) in W:
      pass
    else:
      W.add(str(słowo+'-'+rev(słowo)))
    
print(W)
