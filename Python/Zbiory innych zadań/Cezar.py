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

print(ceasar('juliusz',0))
print(ceasar('cezar',1))


                
