# Stosujemy ogolna metode odwracania polegajaca na uzyciu mask bitowych
# (podobne do zadania z konwersji big-endian na little-endian)
# zaczynamy od najmniejszych elementow:
# kolejno zamieniamy ze soba sasiednie bity: maska 1010... i 0101...
# kolejne pary: 1100 1100... i 0011 0011...
# bloki: 1111 0000... i 0000 1111...
# bajty 1111 1111... i 0000 0000...
# i tak dalej 
# az do momentu gdy zamieniamy kolejnoscia jedna polowe na druga polowe
# co daje nam wynik

	.text
	.global	bitrev
	.type	bitrev, @function

bitrev:
	mov		%rdi, %rax
	
	# Na tym etapie w temp1 wyznaczamy sobie ktore bity chcemy przesunac
	# Przesuwamy je o jedno miejsce w prawo (bo w tym przypadku te dwie maski 
	# maja uwzgledniac zamiane miejscami kolejnych par bitow)
	# stad: w temp1 przesuwamy o jedno miejsce w prawo (bo dany bit chcemy
	# przesunac od jedno miejsce) w temp2 o jedno miejsce w lewo (analogicznie)
	# na koniec or'ujemy te dwie liczby tak by uzupelnic bity w potrzebnych
	# miejscach
	# temp1 = (x & 0xaaaaaaaaaaaaaaaa) >> 1
	# temp2 = (x & 0xaaaaaaaaaaaaaaaa) << 1
	# x = temp1 | temp2
	mov		$0xaaaaaaaaaaaaaaaa, %r8
	and		%rax, %r8
	shr		$1, %r8
	mov		$0x5555555555555555, %r9
	and		%rax, %r9
	shl		$1, %r9
	or		%r8, %r9	
	mov		%r9, %rax

    # analogicznie,
    # ale chcemy przesuniecia 2 sasiednich bitow w miejsce 2 kolejnych
	mov		$0xcccccccccccccccc, %r8
	and		%rax, %r8
	shr		$2, %r8
	mov		$0x3333333333333333, %r9
	and		%rax, %r9
	shl		$2, %r9
	or		%r8, %r9	
	mov		%r9, %rax

    # tu chcemy przeusniecia 4 sasiednich bitow w miejsce 4 kolejnych 
	mov		$0xf0f0f0f0f0f0f0f0, %r8
	and		%rax, %r8
	shr		$4, %r8
	mov		$0x0f0f0f0f0f0f0f0f, %r9
	and		%rax, %r9
	shl		$4, %r9
	or		%r8, %r9	
	mov		%r9, %rax

    # tu chcemy przeusniecia 8 sasiednich bitow w miejsce 8 kolejnych 
	mov		$0xff00ff00ff00ff00, %r8
	and		%rax, %r8
	shr		$8, %r8
	mov		$0x00ff00ff00ff00ff, %r9
	and		%rax, %r9
	shl		$8, %r9
	or		%r8, %r9	
	mov		%r9, %rax

    # tu chcemy przeusniecia 16 sasiednich bitow w miejsce 16 kolejnych 
	mov		$0xffff0000ffff0000, %r8
	and		%rax, %r8
	shr		$16, %r8
	mov		$0x0000ffff0000ffff, %r9
	and		%rax, %r9
	shl		$16, %r9
	or		%r8, %r9	
	mov		%r9, %rax
	
    # tu chcemy przeusniecia 32 sasiednich bitow w miejsce 32 kolejnych
    # (tu nie potrzebujemy juz maski, bo przesuniecie wyzeruje bity)
    # temp1 = (x >> 32) 
    # temp2 = (x << 32)
    # x = temp1 | temp2
	mov		%rax, %r8
	shr		$32, %r8
	mov		%rax, %r9
	shl		$32, %r9
	or		%r8, %r9
	mov		%r9, %rax
    ret

	.size	bitrev, .-bitrev