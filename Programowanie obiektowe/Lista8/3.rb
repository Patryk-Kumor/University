class Jawna
	def initialize(napis)
	@nasz_napis = napis
	end


	def to_s
	return @nasz_napis
	end


	def szyfruj(klucz)
	txt = "" 
	@nasz_napis.each_char do |i|
		txt+= klucz[i]
		end
	return Zaszyfrowane.new( txt )
	end

end


class Zaszyfrowane
	def initialize(napis_szyfrowany)
	@nasz_napis_szyfrowany = napis_szyfrowany
	end


	def to_s
	return @nasz_napis_szyfrowany
	end


	def odszyfruj(klucz)
	txt = ""
	@nasz_napis_szyfrowany.each_char do |i|
		txt+= klucz.key(i)
		end
	return Zaszyfrowane.new( txt )
	return Jawna.new( txt )
	end

end

klucz = {
'a' => 'b',
'b' => 'r',
'r' => 'y',
'y' => 'u',
'u' => 'a'
}

test = Jawna.new("uaabbrryyuu")
puts test
puts test.szyfruj(klucz)

szyfr = test.szyfruj(klucz)
puts szyfr.odszyfruj(klucz)






