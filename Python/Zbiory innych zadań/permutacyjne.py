def permutacja(słowo):
       
        słownik=dict()
        i=1
        for litera in słowo:
                if litera in słownik:
                        pass
                else:
                        słownik[str(litera)]=i
                        i+=1
        w=''
        for litera in słowo:
                w+=str(słownik[str(litera)])+'-'
        return w[:-1]
       

print(permutacja('nie'))
print(permutacja('tata'))
print(permutacja('indianin'))
