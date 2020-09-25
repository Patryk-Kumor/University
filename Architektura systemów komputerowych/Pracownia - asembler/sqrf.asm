	.text
	.global	sqrf
	.type	sqrf, @function
	
sqrf:
    mov %edi, %esi          # kopiowanie float do pomocniczych rejestrow
    mov %edi, %eax 
    cmp $0x80000000, %edi   # sprawdzamy czy liczba = -0
    je rest
    cmp $0x0, %edi          # sprawdzamy czy liczba = 0
    je rest
    and $0x7f800000, %esi   # bity 2-9 - exponent
    add %esi, %esi
    sub $0x3f800000, %esi   # exponent A + exponent B - bias (przesuniete $127)
    and $0x7fffff, %eax     # bity 10-32 - mantisa
    or $0x800000, %eax      # ukryta jedynka do obliczen mnozenia mantysy
    imul %rax, %rax         # mantis A * mantis B 
    mov $0x800000000000, %rdx   # sprawdzamy nadwyzke 
    and %rax, %rdx
    shr $47, %rdx
    cmp $1, %rdx
    je nadwyzka
bez_nadwyzki:
    shr $23, %rax           # przesuniecie mantysy
    jmp rest
nadwyzka:
    shr $24, %rax           # przesuniecie mantysy (uwzglednia nadwyzke)
    add $0x800000, %esi     # dodajemy 1 do exponenty
rest:
    and $0x7fffff, %eax     # pozbycie sie ukrytej jedynki
    or %esi, %eax           # laczenie exponenty i mantysy (sign zawsze 0)
    ret

	.size	sqrf, . - sqrf