from duze_cyfry import dajCyfre
    

def cyfra(n):
    for r in dajCyfre(n):
        print (r)

n=str(input('Podaj liczbę: '))

X=list(n)




def liczba(n):
    i=0
    while i < (len(X)):
        y=float(X[i])
        '{:>10}'.format(str(cyfra(y)))
        i=i+1


liczba(n)
