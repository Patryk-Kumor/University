# Metoda ta polega na sprawdzaniu prefixow za pomoca mask
# (w zasadzie opiera sie na binary searchu)
#
# Na starcie: jezeli caly ciag to zero - zwracamy 64, w innym wypadku:
# sprawdzamy w ktorej polowe istnieje koniec prefixu zerowego 
# (pierwszy zapalony bit) poprzez porownanie ciagu z maskami, ktore oznaczaja 
# bity coraz to mniejszych polow ciagu (odpowiednio przesunietych)
# [ andowanie z dana maska oznaczy bity tylko w danym fragmencie ]

    .text
	.global	clz
	.type	clz, @function

clz:
    mov $0, %eax

# Sprawdzamy czy caly ciag jest zerowy. 
# Jesli jest, to wynik=64, ktory zwracamy go od razu
if_0:
	cmp $0, %rdi
	jne check_32
	add $64, %eax
	jmp fin

# Maska oznacza lewa strone do sprawdzenia
# and'ujemy go z naszym ciagiem, co oznaczy nam ewentualne bity po lewej stronie
# - jesli wynik jest zerowy - to znaczy ze cala lewa strona byla zerowa
# wtedy do wyniku dodajemy 32 i przeuswamy caly ciag o 32,
# po to by w dalszych etapach przejsc do sprawdzenia prawej czesci ciagu
# gdzie prefix zerowy ma szanse sie skonczyc
# - jesli wynik jest niezerowy, to znaczy ze prefix konczy sie gdzies
# w lewej polowie ciagu. Wtedy w dalszym etapie sprawdzania nadal odwolujemy 
# sie do tej lewej czesci ciagu, stad - brak przesuniecia 
check_32:
	mov $0xffffffff00000000, %r8
	and %rdi, %r8
	jz if_32
	jmp check_16
if_32:
	add $32, %eax
	shl $32, %rdi

# Analogicznie, ale teraz wystarczy sprawdzac 16 bitow calego ciagu,
# czyli o polowe mniej
# (lewa lub prawa stona ciagu poczatkowego, liczac od srodka)
check_16:
	mov $0xffff000000000000, %r8
	and %rdi, %r8
	jz if_16
	jmp check_8
if_16:
	add $16, %eax
	shl $16, %rdi

# Analogicznie, jak wyzej
check_8:
	mov $0xff00000000000000, %r8
	and %rdi, %r8
	jz if_8
	jmp check_4
if_8:
	add $8, %eax
	shl $8, %rdi
	
# Analogicznie, jak wyzej
check_4:
	mov $0xf000000000000000, %r8
	and %rdi, %r8
	jz if_4
	jmp check_2
if_4:
	add $4, %eax
	shl $4, %rdi

# Analogicznie, jak wyzej
check_2:
	mov $0xc000000000000000, %r8
	and %rdi, %r8
	jz if_2
	jmp check_1
if_2:
	add $2, %eax
	shl $2, %rdi

# sprawdzamy ostatni bit po lewej (z dwoch pozostalych bitow)
# jesli bit po prawej byl zerowy - to caly ciag byl zerowy,
# co uwzgledniamy juz na starcie przy <if_0>
check_1:
	mov $0x8000000000000000, %r8
	and %rdi, %r8
	jz if_1
	jmp fin
if_1:
	add $1, %eax

fin:
    ret

	.size	clz, .-clz