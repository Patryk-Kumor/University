	.text
	.global	insert_sort
	.type	insert_sort, @function
	
insert_sort:
    lea (%rdi), %rax    # wskaznik na pierwszy elem. tablicy
elem: 
    lea (%rax), %r8     # pobieramy indeks nowego elementu do insertowania
    lea -8(%r8), %r9    # bierzemy poprzedzajacy wskaznik
do:
    cmp %rsi, %r8       # wsk poza tablica -> koniec sortowania
    ja fin
    cmp %rdi, %r9       # wskaznik przed tab -> nastepna liczba do insertowania
    jb brak_swap
    mov (%r8), %rcx    # zaladowanie naszej liczby glownej [rcx] (insertowanej)
    mov (%r9), %rdx    # zaladowanie liczby poprzedzajacej [rdx]
    cmp  %rdx, %rcx    
    jl swap         # rcx < rdx => swap liczb i zmniejszenie wskaznikow
    jmp brak_swap   # rcx > rdx => brak_swap i nastepna liczba do insertowania
swap:
    mov %rcx, (%r9)     # swap liczb
    mov %rdx, (%r8) 
    lea -8(%r8), %r8    # zmniejszanie wskaznikow
    lea -8(%r9), %r9    
    jmp do
brak_swap:
    lea 8(%rax), %rax   #przesuniecie wskaznika "konca" posortowanej listy
    jmp elem
fin:
    ret
    
	.size	insert_sort, . - insert_sort