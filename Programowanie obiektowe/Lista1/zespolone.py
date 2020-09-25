def zespolona(a,b):  # a + b*i
    return [a, b]

def dodaj(z, c):
    return (z[0]+c[0], z[1]+c[1])

def dodaj_b(z, c):
    c[0] += z[0]
    c[1] += z[1]
    return c

def odejmij(z, c):
    return (z[0]-c[0], z[1]-c[1])

def odejmij_b(z, c):
    a = c[0] - z[0]
    b = c[0] - z[1]
    c=[a,b]
    return c

def mnóż(z, c):
    return ( z[0]*c[0] - z[1]*c[1] , z[1]*c[0] + z[0]*c[1] )

def mnóż_b(z,c):
    a = z[0]*c[0] - z[1]*c[1]
    b = z[1]*c[0] + z[0]*c[1]
    c=[a,b]
    return c

def dziel(z,c):
    return ( (z[0]*c[0] + z[1]*c[1])/(c[0]**2+c[1]**2) , (z[1]*c[0] - z[0]*c[1])/(c[0]**2+c[1]**2) )

def dziel_b(z,c):
    a = (z[0]*c[0] + z[1]*c[1])/(c[0]**2+c[1]**2)
    b = (z[1]*c[0] - z[0]*c[1])/(c[0]**2+c[1]**2)
    c=[a,b]
    return c

def wyświetl(z):
    print( str(z[0])+'+'+str(z[1])+'i' )
