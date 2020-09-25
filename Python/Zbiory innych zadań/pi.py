from math import *
pi=list('14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706')
pi2=list('314159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706')

usuń={',','.',':',';',"!",'?','«','»','-','_','(',')','—'}
txt=open('pan_tadeusz.txt', encoding='utf8').read().split()

def suma(lista_znaków):
    w=''
    for znak in lista_znaków:
        w+=znak
    return w

def wyrzuć_znaki(txt):
    bezznakowiec=[]
    for słowo in txt:
        znaki=list(słowo)
        for znak in znaki:
            if znak in usuń:
                znaki.remove(znak)
        w=suma(znaki)
        if w!='':        
            bezznakowiec.append(suma(znaki))
    return bezznakowiec

bez=wyrzuć_znaki(txt)
            
#def string(lista):
#    w=''
#    for liczba in lista:
#        w+=str(liczba)
#    return w
#
#strin=string(cyfry)                #Dowód: Max. Wartość to 5
#
#for i in range(100):       
#    print('Znaki pi od 0 do: ',i+1,' to: ',strin.count(string(pi[1:i+1])))


def szukaj(słowa,pi):
    Maks = []
    najw= 0
    
    for i in range(len(słowa)):
        j = 0
        it = i
        curr = []
        while len(słowa[it])==int(pi[j]):
            curr.append(słowa[it])
            j+=1
            it+=1
            if it>=len(słowa): break
            len(słowa[it])
        if j>najw:
            Maks = curr
            najw = j
    return Maks

print(szukaj(bez,pi))
print(szukaj(bez,pi2))








