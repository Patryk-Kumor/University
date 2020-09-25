from decimal import *

getcontext().prec=102

Liczby_pi = []

b = str(sum(1/Decimal(16)**k * (Decimal(4)/(8*k+1) - Decimal(2)/(8*k+4) - Decimal(1)/(8*k+5) - Decimal(1)/(8*k+6)) for k in range(100)))
b = b[:1] + b[2:]

for x in range (100):
	Liczby_pi.append(int(b[x]))
	
f = open("pan_tadeusz.txt",encoding='utf8').read().split()

DonTadeo=[]
for e in f:
	e = list(e)
	if "?" in e:
		e.remove("?")
	elif "!" in e:
		e.remove("!")
	elif "." in e:
		e.remove(".")
	elif "," in e:
		e.remove(",")
	elif '…' in e:
		e.remove('…')
	elif ":" in e:
		e.remove(":")
	elif ";" in e:
		e.remove(";")
	elif '—' in e:
		e.remove('—')
	elif '«' in e:
		e.remove('«')
	if len(e) != 0:
		slowo = ''.join(e)
	DonTadeo.append(slowo)

dl_slow = []
for element in DonTadeo:
	dl_slow.append(len(element))

wycinek = 0
maks = 0
indeksy = []
prawda = []

for i in range (len(dl_slow)):
	if maks >= wycinek:
		wycinek = maks
		prawda = indeksy
	maks = 0
	indeksy = []
	for j in range (99):
		if int(dl_slow[i+j]) == Liczby_pi[j]:
			maks += 1
			indeksy.append(i+j)
		else:
			break

for element in prawda:
	print (DonTadeo[element])
	
