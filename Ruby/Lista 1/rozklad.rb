require 'prime'
#Prime.take_while {|p| p < n }

def dzielniki(n)
  if (n == 0) or (n == 1)
    []
  else
    tab = []
    primes = Prime.take_while {|p| p < n }
    i=0
    while i < primes.length
      if n % primes[i] == 0
        tab += [primes[i]]
        n = n/primes[i]
      else
        i += 1
      end

    end   
  end
  tab.uniq
end

puts dzielniki(10)
dzielniki(15)
dzielniki(25)
dzielniki(13)
dzielniki(256)
dzielniki(1025) 
puts dzielniki(1048)