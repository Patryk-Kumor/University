class DrzewoBinarne
    class TreeNode
        include Comparable
    
        attr_accessor :value, :left, :right
    
        def initialize (value)
            @value = value
            @left = nil
            @right = nil
        end

        def wstaw(nowy_node)
            if nowy_node >= self
                if self.right then self.right.wstaw(nowy_node)
                else self.right = nowy_node end
            else
                if self.left then self.left.wstaw(nowy_node)
                else self.left = nowy_node end
            end          
        end
    
        def <=> (other_node)
            value <=> other_node.value
        end

        def to_s()
            if left then l = left.to_s else l=nil end
            if right then r = right.to_s else r=nil end
            wynik = []; wynik += l if l; wynik += [@value.to_s]
            wynik += r if r
            wynik
        end

        def to_string()
            if left then l = left.to_string else l="nil" end
            if right then r = right.to_string else r="nil" end
            "[" +@value.to_s+ "," +l+ "," +r+ "]"
        end

        def istnieje?(nowy_node)
            if nowy_node == self
                return true
            else
                if nowy_node > self
                    if self.right then self.right.istnieje?(nowy_node) else false end
                else
                    if self.left then self.left.istnieje?(nowy_node) else false end
                end
            end
        end

        def minimum()
            if self.left.nil?
                return self
            else
                return self.left.minimum()
            end
        end

        def przesun()
            min = self.minimum()
            if self.nil?
                puts "error"
            elsif min==self and self.right
                self.value = self.right.value
                self.left = self.right.left
                self.right = self.right.right
            else
                self.value = min.value
                self.usun_min(min)
            end
        end

        def usun_min(node)
            if (self.left == node)
                self.left = nil
            else #SZUKAMY DALEJ
                self.left.usun(node)
            end
        end
        
        def usun(node)
            if self.left==node
                if self.left.left.nil? and self.left.right.nil? #nie ma dzieci
                    self.left = nil
                elsif self.left.left.nil? and self.left.right #ma tylko prawe dziecko
                    self.left = self.left.right
                elsif self.left.left and self.left.right.nil? #ma tylko lewe dziecko
                    self.left = self.left.left
                else
                    self.left.przesun()
                end

            elsif self.right==node
                if self.right.left.nil? and self.right.right.nil? #nie ma dzieci
                    self.right = nil
                elsif self.right.left.nil? and self.right.right #ma tylko prawe dziecko
                    self.right = self.right.right
                elsif self.right.left and self.right.right.nil? #ma tylko lewe dziecko
                    self.right = self.right.left
                else
                    self.right=nil
                end


            else
                if node > self
                    self.right.usun(node)
                else
                    self.left.usun(node)
                end
            end
        end
    end

##############################################################

    def initialize()
        @root = nil
    end

    def minimum()
        @root.minimum() if @root
    end

    def wstaw(value)
        nowy_node = TreeNode.new(value)
        if @root
            @root.wstaw(nowy_node)
        else
            @root = nowy_node
        end
    end
  
    def istnieje?(value)
        if @root
            nowy_node = TreeNode.new(value)
            @root.istnieje?(nowy_node)
        else
            "empty tree" 
        end
    end    
  
    def usun(value)
        if self.istnieje?(value)
            nowy_node = TreeNode.new(value)
            if (@root.left.nil? and @root.right.nil?) and @root==nowy_node #root do usuniecia nie ma dzieci
                @root=nil
            elsif @root==nowy_node  #root do usuniecia ma dzieci
                @root.przesun()
            else
                @root.usun(nowy_node) #nie usuwamy root
            end
        else 
            "nie istnieje"
        end
    end  

    def to_s()
        if @root 
            @root.to_s
        else
            "empty tree" 
        end
    end

    def to_string()
        if @root 
            @root.to_string
        else
            "empty tree" 
        end
    end
end

class StringBT < DrzewoBinarne
end

puts "\n---Wstawianie---"
puts ""
drzewo = DrzewoBinarne.new()
drzewo.wstaw(1)
drzewo.wstaw(2)
drzewo.wstaw(0)
drzewo.wstaw(3)
drzewo.wstaw(4)
drzewo.wstaw(5)
drzewo.wstaw(7)
drzewo.wstaw(6)
puts "\n---STRING-NODE---"
puts ""
puts drzewo.to_string
puts "\n---ISTNIEJE?---"
puts ""
puts drzewo.istnieje?(7)
puts drzewo.istnieje?(100)
puts drzewo.istnieje?(0)
puts drzewo.istnieje?(10)
puts "\n---INFIX---"
puts ""
puts drzewo.to_s




puts "\n---USUWANIE---"
puts ""
drzewo2 = DrzewoBinarne.new()
drzewo2.wstaw(1)
puts drzewo2.to_string
drzewo2.usun(1)
puts drzewo2.to_s
puts "\n---USUWANIE2---"
puts ""
drzewo3 = DrzewoBinarne.new()
drzewo3.wstaw(0)
drzewo3.wstaw(-8)
drzewo3.wstaw(2)
drzewo3.wstaw(1)
puts drzewo3.to_string
drzewo3.usun(0)
puts "usuń 0"
puts drzewo3.to_string


puts "\n\n---USUWANIE3---"
puts ""
drzewo4 = DrzewoBinarne.new()
drzewo4.wstaw(0)
drzewo4.wstaw(1)
drzewo4.wstaw(2)
drzewo4.wstaw(3)
puts drzewo4.to_string
puts "usuń 0"
drzewo4.usun(0)
puts drzewo4.to_string


puts "\n\n---USUWANIE4---"
puts ""
drzewo5 = DrzewoBinarne.new()
drzewo5.wstaw(0)
drzewo5.wstaw(1)
drzewo5.wstaw(2)
drzewo5.wstaw(4)
drzewo5.wstaw(3)
puts drzewo5.to_string
drzewo5.usun(0)
puts "usuń 0"
puts drzewo5.to_string

puts "\n\n---USUWANIE5---"
puts ""
drzewo6 = DrzewoBinarne.new()
drzewo6.wstaw(0)
drzewo6.wstaw(-10)
drzewo6.wstaw(-15)
drzewo6.wstaw(-20)
drzewo6.wstaw(-5)
puts drzewo6.to_string
drzewo6.usun(-10)
puts "usuń -10"
puts drzewo6.to_string
drzewo6.usun(-20)
puts "usuń -20"
puts drzewo6.to_string
drzewo6.usun(-5)
puts "usuń -5"
puts drzewo6.to_string

puts "\n\n"
drzewo_string = StringBT.new()
drzewo_string.wstaw("pierwszy")
drzewo_string.wstaw("drugi")
drzewo_string.wstaw("trzeci")
drzewo_string.wstaw("do_usunięcia")
drzewo_string.usun("do_usunięcia")
puts drzewo_string.to_s
puts drzewo_string.to_string