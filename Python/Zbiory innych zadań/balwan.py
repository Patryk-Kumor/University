def kolko(n):
    for y in range (n):    
        for x in range (n):
            if ((x-n/2)**2 + (y-n/2)**2) <= ((n*n)/4):
                print('#',end='')
            else:
                print(' ',end='')
        print(end='\n')

def balwan(n):
    for y in range (n):
        
        print((8)*' ', end='')
        for x in range (n):
            if ((x-n/2)**2 + (y-n/2)**2) <= ((n*n)/4):
                print('#',end='')
            else:
                print(' ',end='')
        print(end='\n')
    n=n+5
    for y in range (n):
        print((6)*' ', end='')
        for x in range (n):
            if ((x-n/2)**2 + (y-n/2)**2) <= ((n*n)/4):
                print('#',end='')
            else:
                print(' ',end='')
        print(end='\n')
    n=n+10   
    for y in range (n):
        print((0)*' ', end='')
        for x in range (n):
            if ((x-n/2)**2 + (y-n/2)**2) <= ((n*n)/4):
                print('#',end='')
            else:
                print(' ',end='')
        print(end='\n')
    
        
            
n=int(input('Rozpocznij: '))

balwan(15)
            
