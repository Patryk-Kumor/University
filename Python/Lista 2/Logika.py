from itertools import *



class Formula:
    
    def __init__(self):
        ...
        
    def oblicz(self):
        ...
        
    def __str__(self):
        ...


    
class Zmienna(Formula):
    
    def __init__(self,x):
        if isinstance(x, str):
            if x in ['(', ')', '∨', '∧', '¬', 'True', 'False', '↔', '→']:
                raise RuntimeError("Niedozwolona zmienna")
            else:
                self.wartosc = x
        else:  
            raise RuntimeError("Niezgodny typ zmiennej. Nie jest stringiem")

    def __str__(self):
        return str(self.wartosc)
    
    def oblicz(self,zmienne):
        if self.wartosc in zmienne:
            if isinstance(zmienne[self.wartosc], bool):
                return zmienne[self.wartosc]
            else:
                raise RuntimeError("Niepoprawne odwołanie do zmiennej. Niezgodny typ")  
        else:
            raise RuntimeError("Nie można odwołać się do zmiennej. Brak zmiennej w słowniku")



class true(Formula):
    
    def __init__(self):
        self.wartosc = True
        
    def __str__(self):
        return str(self.wartosc)

    def oblicz(self,zmienne):
        return self.wartosc



class false(Formula):
    
    def __init__(self):
        self.wartosc = False
        
    def __str__(self):
        return str(self.wartosc)

    def oblicz(self,zmienne):
        return self.wartosc



class And(Formula):

    def __init__(self, and1, and2):
        self.wartosc1 = and1
        self.wartosc2 = and2
        
    def __str__(self):
        return "( " + str(self.wartosc1) +" ∧ "+ str(self.wartosc2) + " )"

    def oblicz(self,zmienne):
        return self.wartosc1.oblicz(zmienne) and self.wartosc2.oblicz(zmienne)



class Or(Formula):

    def __init__(self, or1, or2):
        self.wartosc1 = or1
        self.wartosc2 = or2
        
    def __str__(self):
        return "( " + str(self.wartosc1) +" ∨ "+ str(self.wartosc2) + " )"

    def oblicz(self,zmienne):
        return self.wartosc1.oblicz(zmienne) or self.wartosc2.oblicz(zmienne)



class Neg(Formula):

    def __init__(self, formula):
        self.wartosc = formula
        
    def __str__(self):
        return "¬ ( " + str(self.wartosc) + " )"

    def oblicz(self,zmienne):
        return not (self.wartosc.oblicz(zmienne))



class Implies(Formula):

    def __init__(self, im1, im2):
        self.wartosc1 = im1
        self.wartosc2 = im2
        
    def __str__(self):
        return "( " + str(self.wartosc1) +" → "+ str(self.wartosc2) + " )"

    def oblicz(self,zmienne):
        return (not(self.wartosc1.oblicz(zmienne))) or self.wartosc2.oblicz(zmienne)


class Both(Formula):

    def __init__(self, bi1, bi2):
        self.wartosc1 = bi1
        self.wartosc2 = bi2
        
    def __str__(self):
        return "( " + str(self.wartosc1) +" ↔ "+ str(self.wartosc2) + " )"

    def oblicz(self,zmienne):
        return (not(self.wartosc1.oblicz(zmienne)) and not(self.wartosc2.oblicz(zmienne))) or (self.wartosc1.oblicz(zmienne) and self.wartosc2.oblicz(zmienne))



#########################



def szukaj(form):
    string = str(form).split()
    string = set(string)
    T=[' ']
    for i in T:
        if i in string:
            string.remove(i)
    return list(string)

def wartosciowania(lista_zmiennych):
    n=len(lista_zmiennych)
    T=[]
    for i in product([True,False], repeat=n):
        dic={}
        for j in range(n):
            dic.update( {lista_zmiennych[j]:i[j]} )
        T.append(dic)
    return T

    

def tautologia(formula):
    zmienne = szukaj(formula)
    T = wartosciowania(zmienne)
    for i in T:
        if formula.oblicz(i)==False:
            print("To nie jest tautologia")
            print("Dowód:", i, "\n")
            return False
    print("To jest tautologia \n")
    return True



#########################




formula = Implies(Neg(Both(And(true(),Zmienna('p')), Or(Zmienna('r'),Zmienna('q')))),Zmienna('p'))

print (str(formula))

print (formula.oblicz({'p':True,'q':False,'r':False}))

tautologia(formula)

##

formula2 = Or(Zmienna('p'),Neg(Zmienna('q')))

print (str(formula2))

print (formula2.oblicz({'p':True,'q':False,'r':False}))

tautologia(formula2)


##

formula3 = Or(Zmienna('p'),Neg(Zmienna('p')))

print (str(formula3))

print (formula3.oblicz({'p':True,'q':False,'r':False}))

tautologia(formula3)


##

formula4 = Or(Or(Zmienna('p'),Neg(Zmienna('p'))),Neg(Or(Zmienna('p'),Neg(Zmienna('p')))))

print (str(formula4))

print (formula4.oblicz({'p':True,'q':False,'r':False}))

tautologia(formula4)

##

formula5 = Or(Or(Zmienna('p'),Neg(Zmienna('q'))),Neg(Or(Zmienna('r'),Neg(Zmienna('s')))))

print (str(formula5))

print (formula5.oblicz({'p':True,'q':False,'r':False}))

tautologia(formula5)

