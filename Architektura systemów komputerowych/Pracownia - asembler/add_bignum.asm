	.text
	.global	add_bignum
	.type	add_bignum, @function
	
add_bignum:
    lea 4(%rdx), %rax   # wskaznik na poczatek tablicy wynikowej
    mov (%rdi), %r8d    # liczba n w bignum_t a
    mov (%rsi), %r9d    # liczba n w bignum_t b
    cmp %r9, %r8        # IF r8 > r9 THEN GOTO-B
    ja B
#A  # r9 > r8
    lea 4(%rdi), %r10   # wskaznik na poczatek tab o mniejszej liczbie n (z rdi)
    lea 4(%rsi), %r11   # wskaznik na poczatek tab o wiekszej liczbie n
    jmp loopA           # lub rowne
B:  # r8 > r9
    lea 4(%rsi), %r10   # wskaznik na poczatek tab o mniejszej liczbie n (z rsi)
    lea 4(%rdi), %r11   # wskaznik na poczatek tab o wiekszej liczbie n
    xor %r9, %r8        # lub rowne 
    xor %r8, %r9        # swapujemy r8 i r9 zeby to w r8 bylo mniejsze n 
    xor %r9, %r8  
    #mov %r9d, (%rdx)   # wstawiamy nowe n w structa r #  
    #add $1, (%rdx)     # ^ niepotrzebne, bo struct r pomiesci wszystko
    # w r8 mamy liczbe n mniejszej tablicy (jako pierwsza iterowana tablica)
    # w r9 mamy wieksza liczbe n 
loopA:
    cmp $0, %r8d        # sprawdzamy czy pozostaly jakies bajty do wpisania
    je beforeB
    mov (%r10), %cl     # ladujemy liczbe z pierwszej tablicy
    mov %cl, (%rax)     # WSTAWIAMY liczbe do wynikowej tablicy
    lea 1(%r10), %r10   # przechodzimy dalej wskaznikiem - tab
    lea 1(%rax), %rax   # przechodzimy dalej wskaznikiem - tab wynikowa
    dec %r8d            # zmniejszamy ilosc bajtow pozostalych do wpisania
    jmp loopA
beforeB:
    lea 4(%rdx), %rax   # wskaznik wynikowy na poczatek
    mov $0, %bl         # carry_flag = na start 0
loopB:
    cmp $0, %r9d        # sprawdzamy czy pozostaly jakies bajty do dodania
    je fin
    mov (%r11), %cl     # ladujemy liczbe z tablicy
    add %bl, %cl        # dodajemy carry flag z poprzedniej iteracji
    mov $0, %bl         # ustawiamy poprzednie carry jako 0
    adc $0, %bl         # ustawiamy carry poprzed dodanie flagi CF z dodawania 
    add %cl, (%rax)     # DODAJEMY liczbe do wyniku
    adc $0, %bl         # wstawiamy carry flag jesli mialo miejsce   
    lea 1(%r11), %r11   # przechodzimy dalej wskaznikiem - tab
    lea 1(%rax), %rax   # przechodzimy dalej wskaznikiem - tab wynikowa
    dec %r9d
    jmp loopB   
fin:
    add %bl, (%rax)     # dodajemy carry nadwyzkowe 
    ret

	.size	add_bignum, . - add_bignum