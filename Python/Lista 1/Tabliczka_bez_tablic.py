def tabliczka(x1, x2, y1, y2):
    print("      ", end='')
    
    for i in range(y1,y2+1):
        print(i,"   ",end='')

    
    for i in range(x1,x2+1):
        print("\n",i, "   ", end='')

        for j in range(y1,y2+1):
            print(i*j, "   ", end='')


tabliczka(0,5,0,5)
