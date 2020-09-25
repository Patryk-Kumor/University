txt=open('slowa.txt', encoding='utf8').read().split()
txt=sorted(set(txt))



def ceasar(s,k):
	alfabet='aąbcćdeęfghijklłmnńoóprsśtuwyzźż'
	lit_cyf=dict(zip(alfabet,range(32)))
	cyf_lit=dict(zip(range(32),alfabet))
	słowo=list(s)
	w=''
	for i in range (len(słowo)):
		x=słowo[i]
		q=lit_cyf[x]+k
		q=q%32
		m=cyf_lit[q]
		w+=m
	return w

def sprawdź(słowo1, słowo2):
        for i in range (32):
          for j in range( 32):
                if ceasar(słowo1,i)==ceasar(słowo2,j):
                        return True
                if j==31 or i==31:
                        return False
def szukaj(słowo):
        for i in range(32):
                if ceasar(słowo,i) in txt:
                        print(ceasar(słowo,i))
                        

print(ceasar('juliusz',0))
print(ceasar('cezar',1))

print(sprawdź('aba','ącą'))

szukaj('fulfolfu')

for i in txt:
        print(i)

                
