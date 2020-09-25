class Funkcja2 < Proc

	def initialize(&blok)
		@funkcja = blok
	end
	
	

	def value(x,y)	
		@funkcja.call(x,y)
	end
	


	def poziomica(a,b,c,d, wysokosc)
		e = 0.01
		l=[]
		x = a
		y = c
		while x <= b
			while y <=d
				if (value(x,y)-wysokosc).abs < e
					w = [x, y]
					l+=[w]
					end
			y+=e
			end
		x+=e
		end
		return l.to_s
	end



	def objetosc(a,b,c,d)
		objetosc=0
		e = 0.01
		x = a
		y = c
		while x <= b
			while y <=d	
			objetosc+=value(x,y)*e*e	
			y+=e
			end
		x+=e
		end

		return objetosc
	end
	

	
end

puts "f(x) = x^2+y^2"

nasza_funkcja = Funkcja2.new { |x, y| x*x+y*y }
puts nasza_funkcja.value(1,1)
puts nasza_funkcja.poziomica(1,2,0,4, 1)
puts nasza_funkcja.objetosc(1,2,0,4)

