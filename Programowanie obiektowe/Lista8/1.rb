class Fixnum
	
	
	def czynniki
		return [] if self == 0
		n = self
		tab = [1]
		return tab if n == 1
		for i in 2...n
			if n % i == 0 
				tab+=[i]
			end
		end	
		return (tab+[n])
	end

	
	def ack(y)
		return y+1 if self == 0
		return (self - 1).ack(1) if y == 0
		return (self-1).ack(self.ack(y-1))
	end

	
	def perfect?
		return false if self == 0
		s = 0
		for i in self.czynniki
			s+=i
		end
		return  (s-self == self)
		
	end
	
	
	Cyfry = ["zero", "jeden", "dwa", "trzy", "cztery", "piec", "szesc", "siedem", "osiem", "dziewiec"]
	def slownie
		 return Cyfry[0] if self == 0
		n = self
		tab = []
		until n==0
			a = n % 10
			tab += [Cyfry[a]]
			n = n / 10
			end
		return tab.reverse.join(" ")
	end
	
end


puts 0.czynniki.to_s
puts " "
puts 5.czynniki.to_s
puts " "
puts 30.czynniki.to_s
puts " "

puts 1.ack(1)
puts 2.ack(1)
puts " "


puts 6.perfect?
puts 28.perfect?
puts 496.perfect?
puts 0.perfect?
puts 1.perfect?
puts 2.perfect?
puts 20.perfect?
puts 100.perfect?
puts " "

puts 123.slownie
puts 987987.slownie
puts 101.slownie
puts 1.slownie
puts 0.slownie
