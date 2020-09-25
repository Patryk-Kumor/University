from duze_cyfry import dajCyfre

def cyfra(n):
    for r in dajCyfre(n):
        print (r)

m=int(input('Podaj cyfrę: '))
X=list(str(m))
print(X)


i=0
if X[(i)] == [0]:
    cyfra(0)
    i=i+1
if X[1] == [1]:
    cyfra(1)

cyfra(int(X[0]))
