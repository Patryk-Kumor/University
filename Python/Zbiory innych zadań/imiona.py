import random

txt=open('Imiona.txt', encoding='utf8').read().split()


alfabet=(list('aąbcćdeęfghijklłmnńoóprsśtuwyzźż'))

def szukaj(litera, słowo):
        w=set()
        słowo=list(słowo)
        for i in range(len(słowo)):
            if litera == słowo[i]:
                if i == len(słowo)-1:
                    pass
                else:
                    w.add(słowo[i+1])
        return w
def szukaj_2(litery, słowo):
        w=set()
        słowo=list(słowo)
        for i in range(len(słowo)):
            if litery == słowo[i-1]+słowo[i]:
                if i == len(słowo):
                    break
                else:
                    w.add(słowo[i+1])
        return w

def następniki(litera):
    następnik=set()
    for słowo in txt:
        if (litera in słowo) and (litera != słowo[-1]):
            następnik.update(szukaj(litera, słowo))
        else:
            pass
    return następnik

def następniki_2(litery):
    następnik=set()
    for słowo in txt:
        if (litery in słowo) and (litery != słowo[-2]+słowo[-1]):
            następnik.update(szukaj_2(litery, słowo))
        else:
            pass
    return następnik

def generuj(k):
        pierwsza=random.sample(alfabet,1)[0]
        druga=random.sample(następniki(pierwsza),1)[0]
        w=(pierwsza+druga)
        for i in range(k):
                x=random.sample(następniki_2(pierwsza+druga),1)[0]
                w+=x
                pierwsza=druga
                druga=x
        print(w)
        
generuj(6)
