def krzyzyk(n):
   for i in range(n):
      print(n*str(' ')+n*str('*'))
   for i in range(n):
      print(3*n*(str('*')))
   for i in range(n):
      print(n*str(' ')+n*str('*'))
   
n=int(input('Podaj n: '))

krzyzyk(n)
