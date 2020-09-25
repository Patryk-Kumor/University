import random

txt=open('Imiona.txt', encoding='utf8').read().split()
for słowo in txt:
        słowo=słowo+'$'

alfabet=(list('aąbcćdeęfghijklłmnńoóprsśtuwyzż'))
def pierwsza_szukana():
        L=[]
        for słowo in txt:
            L.append(słowo[0])    
        return random.choice(L)
def szukaj(litera, słowo):
        w=[]
        słowo=list(słowo)
        for i in range(len(słowo)):
            if litera == słowo[i]:
                if i == len(słowo)-1:
                    pass
                else:
                    w.append(słowo[i+1])
        return w
def szukaj_2(litery, słowo):
        w=[]
        słowo=list(słowo)
        for i in range(len(słowo)):
            if litery == słowo[i-1]+słowo[i]:
                if i == len(słowo):
                    break
                else:
                    w.append(słowo[i+1])
        return w

def następniki(litera):
    następnik=[]
    for słowo in txt:
        if (litera in słowo) and (litera != słowo[-1]):
            następnik.append(szukaj(litera, słowo))
        else:
            pass
    return następnik

def następniki_2(litery):
    następnik=[]
    for słowo in txt:
        if (litery in słowo) and (litery != słowo[-2]+słowo[-1]):
            następnik+=(szukaj_2(litery, słowo))
        else:
            pass
    return następnik

def generuj(k):
        pierwsza=pierwsza_szukana()
        druga=random.choice(następniki(pierwsza))[0]
        w=(pierwsza+druga)
        for i in range(k):
                x=random.choice(następniki_2(pierwsza+druga))[0]
                w+=x
                pierwsza=druga
                druga=x
        print(w)
def generowanie():
        pierwsza=pierwsza_szukana()
        druga=random.choice(następniki(pierwsza))[0]
        w=(pierwsza+druga)
        print('W:',w)
        while True:
                if '$'== w[-1]:
                        print(w)
                else:
                        x=random.choice(następniki_2(pierwsza+druga))[0]
                        print(x)
                        w+=x
                        print(w)
                        pierwsza=druga
                        druga=x
                        print(pierwsza,druga,x)

generowanie()
