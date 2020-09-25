from time import*
L=[]


with open('slowa.txt',encoding="utf8") as f:
  L= f.read().splitlines()#nie append dodawało także nowa linie

def zamien_na_słownik(słowo):
  a=1
  słownik={}
  for i in słowo:
    if i in słownik:
      słownik[i] +=1
    else:
      słownik[i]=1
  return słownik


def funkcja(imie):
    L2=[]
    imie_zbiór=set(imie)
    for wyraz in L:
      if set(wyraz).issubset(imie_zbiór) and len(wyraz)<len(imie):
        L2.append(wyraz)
    print('done')
    print(len(L2))
    return(L2)


def funkcja2(słowo,słowo2,imie,a):
          zmienna=zamien_na_słownik(imie)
          zmienna2=zamien_na_słownik(a)
          for litera in zmienna:
            try:
              if zmienna[litera]!=zmienna2[litera]:
                return False
            except:
              return False
          return słowo,słowo2
        
def główna(imie):
      L3=[]
      L2=funkcja(imie)
      for słowo in L2:
        for słowo2 in L2:
          a=słowo+słowo2
          if len(a)==len(imie):
            temp=funkcja2(słowo,słowo2,imie,a)
            if temp!=False:
              L3.append(temp)
      for i in L3:
        if i[::-1] in L3:
          L3.remove(i)
      for i in L3:
        print(i[0],i[1])
a=time()          
główna('barackobama')
b=time()
c=b-a
print(c)
x=input()










