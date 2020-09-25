import random

def rzut_kostka():
    return random.randint(1, 6)


def gra(n):
    player_one = 0
    player_two = 0
    
    for i in range(n):
        r = runda()
        if r==1:
                player_one = player_one + 1 
        elif r==2:
                player_two = player_two + 1
        else:
            print()
            
        print("Runda: ", i+1)
        print("Gracz 1: ", player_one, "zwycięstw \nGracz 2: ", player_two, "zwycięstw")
        print('---')

    if player_one > player_two:
        print ("--- Grę wygrywa gracz 1 --- \n")
    elif player_one < player_two:
        print ("--- Grę wygrywa gracz 2 --- \n")
    else:
        print ("Remis, \n teraz nastąpi gra do pierwszego zwycięstwa \n")
        r = runda()
        while r == 0:
            r = runda()
        if r==1:
            print ("--- Grę wygrywa gracz 1 --- \n")
        elif r==2:
            print ("--- Grę wygrywa gracz 2 --- \n")

            
def runda():
    a=rzut_kostka()
    b=rzut_kostka()
    c1=a+b
    print ("Gracz 1 wyrzucił: ", a, " oraz ", b, ". W sumie: ", c1)

    a=rzut_kostka()
    b=rzut_kostka()
    c2=a+b
    print ("Gracz 2 wyrzucił: ", a, " oraz ", b, ". W sumie: ", c2)

    if c1>c2:
        print ("Rundę wygrywa gracz 1 \n")
        return 1
    elif c1==c2:
        print ("Rundę wygrywa gracz 2 \n")
        return 2
    else:
        print ("Runda zremisowana")
        return 0
