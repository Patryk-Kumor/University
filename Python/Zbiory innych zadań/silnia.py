from math import factorial

print('Silnia liczby naturalnej n,\nto iloczyn wszystkich liczb naturalnych nie większych niż n.\n')

n=int(input('Podaj liczbę n: '))

for i in range(n+1):
    print(str(i)+'! ma',len(str(factorial(i))), end='')
    X = str(len(str(factorial(i))))
    string = X
    if i < 4:
        if X[-1:] == '1':
            print(' cyfrę')
    if i >= 4:
        if X[-1:] == '2':
            print(' cyfry')
        elif X[-1:] == '3':
            print(' cyfry')
        elif X[-1:] == '4':
            print(' cyfry')
        else:
            print(' cyfr')
