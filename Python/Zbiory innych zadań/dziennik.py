linie=[x.split() for x in open('plik.txt')]

def średnia(L):
    w=0
    for element in L:
        w+=int(element)
    return w/len(L)


osoby=set() #PRZYGOTOWANIE OSÓB
for linia in linie:
    osoby.add(linia[0])


dziennik={} #PRZYGOTOWANIA DZIENNIKA
for p in osoby: #czysty dziennik
    dziennik[p]={}  
for L in linie: #dziennik wypełniony ocenami
    uczeń=L[0]
    przedmiot=L[1]
    oceny=L[2:]
    if przedmiot not in dziennik[uczeń]:
        dziennik[uczeń][przedmiot]=[]
    dziennik[uczeń][przedmiot]+=oceny  
for uczeń in dziennik:  #dziennik wypełniony średnią z ocen dla poszczególnych przedmiotów
    for przedmiot in dziennik[uczeń]:
        dziennik[uczeń][przedmiot]=średnia(dziennik[uczeń][przedmiot])
        

def raport_o_ocenach(osoba):    #Raport dla osoby
        print('KTO:',osoba)
        for przedmiot in dziennik[osoba]:
            print ('  -średnia z',przedmiot,':',dziennik[osoba][przedmiot])

def prymusi(dziennik):  #Lista prymusów i ich średnia
    L={}
    W=set()
    for uczeń in dziennik:
        średnia=0
        for przedmiot in dziennik[uczeń]:
            średnia+=dziennik[uczeń][przedmiot]
        średnia=średnia/len(dziennik[uczeń])
        L[uczeń]=średnia
    maks=0
    for uczeń in L:
        if L[uczeń]>=maks:
            maks=L[uczeń]
    for uczeń in L:
        if L[uczeń]==maks:
            W.add(uczeń)
    print('Nasz prymus/nasi prymusi: ',W)
    print('O średniej:',maks)
    
prymusi(dziennik)
