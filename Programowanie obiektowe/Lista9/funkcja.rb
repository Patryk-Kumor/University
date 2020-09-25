class Funkcja < Proc

	def initialize(&blok)
		@funkcja = blok
	end
	
	
	def value(x)	
		@funkcja.call(x)
	end
	
	
	def zerowe(a, b, eps)
		x = (a+b)/2.0
		val = value(x)
		if val >= -eps and val <= eps
			return x
		else
			left = value(a)
			right = value(b)
			if (left < 0 and val > 0) or (left > 0 and val < 0)
				return zerowe(a,x,eps)
			elsif (right > 0 and val < 0) or (right < 0 and val > 0)
				return zerowe(x,b,eps)
			elsif value == 0 
				return x
			else
				nil
			end
		end
	end

	
	def pole(a,b)
		pole = 0
		e = 0.0001
		x = a
		while x <= b
				pole += value(x)*e
				x += e
			end
		return pole
	end
	
	
	def poch(x)
		h = 0.0000000001
		x2=x+h
		return (value(x2)-value(x))/h
	end
	
	
end
puts "f(x)"

nasza_funkcja = Funkcja.new { |x| x*x }
puts nasza_funkcja.value(1)
puts nasza_funkcja.zerowe(-2, 2, 0.0001)

puts nasza_funkcja.value(0)
puts nasza_funkcja.value(2)
puts nasza_funkcja.pole(0,2)
puts nasza_funkcja.poch(1)