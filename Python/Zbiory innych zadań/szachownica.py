def szachownica(n,k):
    for i in range(n):
        for i in range (k):
            print(n*(k*' '+k*'*'))
        for i in range (k):
            print(n*(k*'*'+k*' '))

n=int(input('Podaj n: '))
k=int(input('Podaj k: '))

szachownica(n,k)
