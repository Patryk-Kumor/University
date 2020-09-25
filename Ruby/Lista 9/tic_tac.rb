require 'tk'  

class Okienko

  def win
    @label2.text = 'KONIEC GRY'
  end

  def pierwszy_gracz
    @gracz_pierwszy = !@gracz_pierwszy
    reset
  end

  def ustaw_O
    @gracz = "O"
    @comp = "X"
    @label.text = "Grasz jako 'O' "
    reset
  end

  def ustaw_X
    @gracz = "X"
    @comp = "O"
    @label.text = "Grasz jako 'X' "
    reset
  end

  def reset
    @tab = [["", "", "",],
            ["", "", "",],
            ["", "", "" ]]
    @label2.text = ''
    @r1c1.text=''; @r1c2.text=''; @r1c3.text=''
    @r2c1.text=''; @r2c2.text=''; @r2c3.text=''
    @r3c1.text=''; @r3c2.text=''; @r3c3.text=''
    if @gracz_pierwszy == false
      computer
    end
    puts "Zresetowano\n\n"
  end

  def rysuj
    s = ''
    s += @r1c1.text + ", "
    s += @r1c2.text + ", "
    s += @r1c3.text + "\n"

    s += @r2c1.text + ", "
    s += @r2c2.text + ", "
    s += @r2c3.text  + "\n"

    s += @r3c1.text + ", "
    s += @r3c2.text + ", "
    s += @r3c3.text  + "\n"     
    print s + "\n"

    print "\n\n\n#{@tab[0][0]} , #{@tab[0][1]}, #{@tab[0][2]}\n"
    print "#{@tab[1][0]} , #{@tab[1][1]}, #{@tab[1][2]}\n"
    print "#{@tab[2][0]} , #{@tab[2][1]}, #{@tab[2][2]}\n\n\n"
  end

  def change(r,c)
    
    rc = eval "@r#{r}c#{c}.text"
    if rc != '' 
      @label2.text = 'Tu nie można'
      #puts "Nie zmieniono dla r#{r}c#{c}"
    else
      @label2.text = ''
      @tab[r-1][c-1] = "#{@gracz}"
      s = "@r#{r}c#{c}.text = '#{@gracz}' "
      eval s
      if check 
        @label2.text = 'Wygrałeś'
        return 0
      end
      if check_all
        @label2.text = 'Remis'
        return 0
      end
      computer
      if check 
        @label2.text = 'Przegrałeś' 
        return 0
      end
      if check_all
        @label2.text = 'Remis'
        return 0
      end
    end
  end
###############################################################################
  def dwa_poziomo(r)
    if @tab[r][0] == @tab[r][1] && @tab[r][0] != '' && @tab[r][2] == ''
      @tab[r][2] = "#{@comp}"
      eval "@r#{r+1}c#{2+1}.text = '#{@comp}' "
      return true 
    elsif @tab[r][0] == @tab[r][2] && @tab[r][0] != '' && @tab[r][1] == ''
      @tab[r][1] = "#{@comp}" 
      eval "@r#{r+1}c#{1+1}.text = '#{@comp}' "
      return true
    elsif @tab[r][1] == @tab[r][2] && @tab[r][1] != '' && @tab[r][0] == ''
      @tab[r][0] = "#{@comp}" 
      eval "@r#{r+1}c#{0+1}.text = '#{@comp}' "
      return true
    else 
      return false
    end
  end
  
  def dwa_pionowo(c)
    if @tab[0][c] == @tab[1][c] && @tab[0][c] !='' && @tab[2][c] ==''
      @tab[2][c] = "#{@comp}" 
      eval "@r#{2+1}c#{c+1}.text = '#{@comp}' "
      return true
    elsif @tab[0][c] == @tab[2][c] && @tab[0][c] !='' && @tab[1][c] ==''
      @tab[1][c] = "#{@comp}" 
      eval "@r#{1+1}c#{c+1}.text = '#{@comp}' "
      return true
    elsif @tab[1][c] == @tab[2][c] && @tab[1][c] !='' && @tab[0][c] ==''
      @tab[0][c] = "#{@comp}" 
      eval "@r#{0+1}c#{c+1}.text = '#{@comp}' "
      return true
    else 
      return false
    end
  end

  def skosy()
    if @tab[0][0] == @tab[1][1] && @tab[0][0] != '' && @tab[2][2] == ''
      @tab[2][2] = "#{@comp}" 
      puts "@r#{2+1}c#{2+1}.text = '#{@comp}' ||1"
      eval "@r#{2+1}c#{2+1}.text = '#{@comp}' "
      return true
    elsif @tab[0][0] == @tab[2][2] && @tab[0][0] != '' && @tab[1][1] == ''
      @tab[1][1] = "#{@comp}" 
      puts "@r#{1+1}c#{1+1}.text = '#{@comp}' ||2"
      eval "@r#{1+1}c#{1+1}.text = '#{@comp}' "
      return true
    elsif @tab[1][1] == @tab[2][2] && @tab[1][1] != '' && @tab[0][0] == ''
      @tab[0][0] = "#{@comp}" 
      puts "@r#{0+1}c#{0+1}.text = '#{@comp}' ||3"
      eval "@r#{0+1}c#{0+1}.text = '#{@comp}' "
      return true

    elsif @tab[0][2] == @tab[1][1] && @tab[0][2] != '' && @tab[2][0] == ''
      @tab[2][0] = "#{@comp}" 
      puts eval "@r#{2+1}c#{0+1}.text = '#{@comp}' ||4"
      eval "@r#{2+1}c#{0+1}.text = '#{@comp}' "
      return true
    elsif @tab[0][2] == @tab[2][0] && @tab[0][2] != '' && @tab[1][1] == ''
      @tab[1][1] = "#{@comp}" 
      puts eval "@r#{1+1}c#{1+1}.text = '#{@comp}' ||5"
      eval "@r#{1+1}c#{1+1}.text = '#{@comp}' "
      return true
    elsif @tab[2][0] == @tab[1][1] && @tab[2][0] != '' && @tab[0][2] == ''
      @tab[0][2] = "#{@comp}" 
      puts eval "@r#{0+1}c#{2+1}.text = '#{@comp}' ||6"
      eval "@r#{0+1}c#{2+1}.text = '#{@comp}' "
      return true
    else
      return false
    end
  end

  def computer
    if dwa_poziomo(0)
      puts "- wykonano ruch komputera poziom0"
    elsif dwa_poziomo(1)
      puts "- wykonano ruch komputera poziom1"
    elsif dwa_poziomo(2)
      puts "- wykonano ruch komputera poziom2"
    elsif dwa_pionowo(0)
      puts "| wykonano ruch komputera pion0"
    elsif dwa_pionowo(1)
      puts "| wykonano ruch komputera pion1"
    elsif dwa_pionowo(2)
      puts "| wykonano ruch komputera pion2"
    elsif skosy()
      puts "/ wykonano ruch komputera skos"
    else
      r = rand(3)
      c = rand(3)
      while true
        puts "r:#{r}, c:#{c}"
        if @tab[r][c] == ''
          @tab[r][c] = "#{@comp}" 
          eval "@r#{r+1}c#{c+1}.text = '#{@comp}' "
          puts "wykonano ruch komputera los"
          return 0
        else
          r = rand(3)
          c = rand(3)
        end
      end
    end
  end
###############################################################################
  def check
    t = @tab
    if (t[0][0] == t[0][1] && t[0][2] == t[0][0] && t[0][0] != "") or
       (t[1][0] == t[1][1] && t[1][2] == t[1][0] && t[1][0] != "") or
       (t[2][0] == t[2][1] && t[2][2] == t[2][0] && t[2][0] != "") or

       (t[0][0] == t[1][0] && t[2][0] == t[0][0] && t[0][0] != "") or
       (t[0][1] == t[1][1] && t[2][1] == t[0][1] && t[0][1] != "") or
       (t[0][2] == t[1][2] && t[2][2] == t[0][2] && t[0][2] != "") or

       (t[0][0] == t[1][1] && t[0][0] == t[2][2] && t[0][0] != "") or
       (t[0][2] == t[1][1] && t[0][2] == t[2][0] && t[0][2] != "") 
          win
          return true
    else
          return false
    end
  end

  def check_all
    t = @tab
    if t[0][0] != '' and t[0][1] != '' and t[0][2] != '' and 
       t[1][0] != '' and t[1][1] != '' and t[1][2] != '' and 
       t[2][0] != '' and t[2][1] != '' and t[2][2] != '' 
      return true
    else
      return false
    end

  end

  def run
    #init
    @tab = [ ["", "", "",],
             ["", "", "",],
             ["", "", "" ] ]
    @gracz_pierwszy = true        
    @gracz = "X"
    @comp = "O"

    @win = TkRoot.new { title "Tic Tac Toe"; minsize(45,45) }
    root = @win
    @label = TkLabel.new(@win) { text "Grasz jako 'X'"; grid('row'=>0, 'column'=>2); width 15;  }
    @label2 = TkLabel.new(@win) { text ' '; grid('row'=>1, 'column'=>2); width 15;  }
    menu = TkMenu.new()
    one = TkMenu.new(menu)
    menu.add('cascade', :menu => one, :label => 'Funkcje')
    one.add('command', :label => 'reset', :command => proc { reset } )
    one.add('command', :label => 'Ustaw gracza jako O', :command => proc { ustaw_O } )
    one.add('command', :label => 'Ustaw gracza jako X', :command => proc { ustaw_X } )
    one.add('command', :label => 'Zmień kolejność graczy', :command => proc { pierwszy_gracz } )
    one.add('command', :label => 'RYSUJ DEBUG', :command => proc { rysuj } )
    root.menu(menu)

    @r1c1 = TkButton.new(@win) { text ''; grid('row'=>2, 'column'=>1); width 5; height 4;  }
    @r1c1.command { self.change(1,1) }
    @r1c2 = TkButton.new(@win) { text ''; grid('row'=>2, 'column'=>2); width 5; height 4; }
    @r1c2.command { self.change(1,2) }
    @r1c3 = TkButton.new(@win) { text ''; grid('row'=>2, 'column'=>3); width 5; height 4; }
    @r1c3.command { self.change(1,3) }

    @r2c1 = TkButton.new(@win) { text ''; grid('row'=>3, 'column'=>1); width 5; height 4; }
    @r2c1.command { self.change(2,1) }
    @r2c2 = TkButton.new(@win) { text ''; grid('row'=>3, 'column'=>2); width 5; height 4; }
    @r2c2.command { self.change(2,2) }
    @r2c3 = TkButton.new(@win) { text ''; grid('row'=>3, 'column'=>3); width 5; height 4; }
    @r2c3.command { self.change(2,3) }

    @r3c1 = TkButton.new(@win) { text ''; grid('row'=>4, 'column'=>1); width 5; height 4; }
    @r3c1.command { self.change(3,1) }
    @r3c2 = TkButton.new(@win) { text ''; grid('row'=>4, 'column'=>2); width 5; height 4; }
    @r3c2.command { self.change(3,2) }
    @r3c3 = TkButton.new(@win) { text ''; grid('row'=>4, 'column'=>3); width 5; height 4; }
    @r3c3.command { self.change(3,3) }


    #TK Loop
    Tk.mainloop
  end

end

x = Okienko.new
x.run