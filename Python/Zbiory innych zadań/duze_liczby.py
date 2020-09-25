from duze_cyfry import dajCyfre
    

def cyfra(n):
    for r in dajCyfre(n):
        print (r)

n=str(input('Podaj liczbę: '))

X=list(n)

for i in range(len(X)) :
    if X[i] == '0':
        cyfra(0)
    elif X[i] == '1':
        cyfra(1)       
    elif X[i] == '2':
        cyfra(2)  
    elif X[i] == '3':
        cyfra(3)
    elif X[i] == '4':
        cyfra(4)
    elif X[i] == '5':
        cyfra(5)           
    elif X[i] == '6':
        cyfra(6)
    elif X[i] == '7':
        cyfra(7)
    elif X[i] == '8':
        cyfra(8)
    elif X[i] == '9':
        cyfra(9)
    elif X[i] == '-':
        cyfra(10)
    else:
        cyfra(666)
    print()


