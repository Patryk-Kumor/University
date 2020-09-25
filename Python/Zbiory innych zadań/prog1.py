def kwadrat(n):
   for i in range(n):
      for j in range(n):
         print ("*", end="")
      print()
      
def kwadrat2(n):
   for i in range(n):
      print (n * "#")      
  

for i in range(10):
   print ("Przebieg:",i)
   if i < 5 :
      kwadrat(2*i+3)
   else:
      kwadrat2(i-2)
   print()
