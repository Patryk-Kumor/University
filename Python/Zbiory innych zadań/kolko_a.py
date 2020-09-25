def kolko(n):
    
    for y in range (n):    
        for x in range (n):
            if ((x-n/2)**2 + (y-n/2)**2) <= ((n*n)/4):
                print('#',end='')
            else:
                print(' ',end='')
        print(end='\n')
            
            
        

n=int(input('Podaj n'))

kolko(n)
            
