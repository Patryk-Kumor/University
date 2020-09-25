class Wyrazenie
    def to_s()
      raise 'not implemented'
    end

    def oblicz(zmienne)
        raise 'not implemented'
    end    

    def uproszczenie()
        raise 'not implemented'
    end  
end

class Zmienna < Wyrazenie
    def initialize(name)
        @zmienna = name
    end        
    def to_s()
        @zmienna.to_s
    end
    def oblicz(zmienne)
        if zmienne[@zmienna] then zmienne[@zmienna] else raise 'no var' end
    end
    def uproszczenie()
        @zmienna.to_s
    end  
end

class Stala < Wyrazenie
    def initialize(value)
        @wartosc = value
    end        
    def to_s()
        @wartosc.to_s
    end
    def oblicz(zmienne)
        @wartosc
    end
    def uproszczenie()
        @wartosc.to_s
    end  
end

class Dodaj < Wyrazenie
    def initialize(wyrazenie1, wyrazenie2)
        @wyr1 = wyrazenie1
        @wyr2 = wyrazenie2     
    end 
    def to_s()
        @wyr1.to_s + "+" + @wyr2.to_s
    end
    def oblicz(zmienne)
        @wyr1.oblicz(zmienne) + @wyr2.oblicz(zmienne)
    end 
    def uproszczenie()
        if @wyr1.uproszczenie()=="0" then @wyr2.uproszczenie()
        elsif @wyr2.uproszczenie()=="0" then @wyr1.uproszczenie()
        else
            @wyr1.uproszczenie() + "+" + @wyr2.uproszczenie()
        end
    end   
end

class Odejmij < Wyrazenie
    def initialize(wyrazenie1, wyrazenie2)
        @wyr1 = wyrazenie1
        @wyr2 = wyrazenie2     
    end 
    def to_s()
        @wyr1.to_s + "-" + @wyr2.to_s
    end
    def oblicz(zmienne)
        @wyr1.oblicz(zmienne) + @wyr2.oblicz(zmienne)
    end 
    def uproszczenie()
        return "0" if @wyr1.uproszczenie == "0" and @wyr2.uproszczenie == "0"
        return @wyr1.uproszczenie if @wyr2.uproszczenie == "0"
        return "-"+@wyr2.uproszczenie if @wyr1.uproszczenie == "0"
        b = @wyr2.uproszczenie
        b=b[2..-1] if b[0..1]=="--"
        if b[0]=="-" 
            return @wyr1.uproszczenie + "+" + b[1..-1]
        else
            return @wyr1.uproszczenie + "-" + b
        end
    end   
end

class Podziel < Wyrazenie
    attr_accessor :wyr1, :wyr2
    def initialize(wyrazenie1, wyrazenie2)
        @wyr1 = wyrazenie1
        @wyr2 = wyrazenie2     
    end 
    def to_s()
        "(" + @wyr1.to_s + ")/(" + @wyr2.to_s + ")"
    end
    def oblicz(zmienne)
        @wyr1.oblicz(zmienne) / @wyr2.oblicz(zmienne)
    end 
    def uproszczenie()
        return @wyr1.uproszczenie if @wyr2.uproszczenie=="1"
        return "(" + @wyr1.uproszczenie + ")/(" + @wyr2.uproszczenie + ")"
    end   
end

class Pomnoz < Wyrazenie
    def initialize(wyrazenie1, wyrazenie2)
        @wyr1 = wyrazenie1
        @wyr2 = wyrazenie2     
    end 
    def to_s()
        "(" + @wyr1.to_s + ")*(" + @wyr2.to_s + ")"
    end
    def oblicz(zmienne)
        @wyr1.oblicz(zmienne) * @wyr2.oblicz(zmienne)
    end 
    def uproszczenie()
        if @wyr2.class == Podziel.new(Stala.new(1),Stala.new(1)).class
            return @wyr2.wyr1.uproszczenie() if @wyr2.wyr2.uproszczenie()==@wyr1.uproszczenie()
        elsif @wyr1.class == Podziel.new(Stala.new(1),Stala.new(1)).class
            return @wyr1.wyr1.uproszczenie() if @wyr1.wyr2.uproszczenie()==@wyr2.uproszczenie()
        else
            return @wyr2.uproszczenie if @wyr1.uproszczenie=="1"
            return @wyr1.uproszczenie if @wyr2.uproszczenie=="1"
            return "(" + @wyr1.uproszczenie + ")*(" + @wyr2.uproszczenie + ")"
        end
    end   
end
######################################################################################################################
######################################################################################################################

expr1 = Zmienna.new("x")
expr2 = Stala.new(1)
expr3 = Stala.new(0)
expr4 = Dodaj.new(expr1,expr2)
expr5 = Dodaj.new(Dodaj.new(Dodaj.new(expr2,expr3), Dodaj.new(expr3,expr2)), Dodaj.new(Stala.new(0), Stala.new(0)))
expr5_2 = Odejmij.new(Odejmij.new(Odejmij.new(Stala.new(0),Stala.new(0)), Odejmij.new(Stala.new(0),Stala.new(0))), Odejmij.new(Stala.new(0), Stala.new(0)))
expr6 = Odejmij.new(Odejmij.new(Odejmij.new(expr2,expr3), Odejmij.new(expr3,expr2)), Odejmij.new(Stala.new(0), Stala.new(0)))
puts expr4
puts expr4.oblicz({"x"=>1})
puts ""
puts expr5
puts expr5.uproszczenie
puts ""
puts Odejmij.new(Stala.new(0), Stala.new(0))
puts Odejmij.new(Stala.new(0), Stala.new(0)).uproszczenie
puts ""
puts Odejmij.new(Stala.new(1), Stala.new(0))
puts Odejmij.new(Stala.new(1), Stala.new(0)).uproszczenie
puts ""
puts Odejmij.new(Stala.new(0), Stala.new(1))
puts Odejmij.new(Stala.new(0), Stala.new(1)).uproszczenie
puts ""
puts expr5_2
puts expr5_2.uproszczenie
puts ""
puts expr6
puts expr6.uproszczenie
expr7 = Podziel.new(Stala.new(1), Stala.new(2))
puts ""
puts expr7
puts expr7.uproszczenie
expr8 = Podziel.new(Dodaj.new(Stala.new(1),Stala.new(1)), Stala.new(1))
puts ""
puts expr8
puts expr8.uproszczenie
expr7 = Pomnoz.new(Stala.new(1), Stala.new(2))
puts ""
puts expr7
puts expr7.uproszczenie
expr8 = Pomnoz.new(Dodaj.new(Stala.new(1),Stala.new(1)), Stala.new(1))
puts ""
puts expr8
puts expr8.uproszczenie
puts ""
expr_a = Dodaj.new(Zmienna.new("x"), Odejmij.new(Stala.new(0), Dodaj.new(Zmienna.new("y"), Stala.new(5))))
puts expr_a
puts expr_a.uproszczenie
expr_b = Podziel.new(Stala.new(1), expr_a)
expr_c = Pomnoz.new(expr_a, expr_b)
puts ""
puts expr_c
puts expr_c.uproszczenie
expr_d = Pomnoz.new(expr_b, expr_a)
puts ""
puts expr_d
puts expr_d.uproszczenie