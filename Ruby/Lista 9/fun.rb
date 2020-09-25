require 'tk'  



class Okienko

  def run
    #init
    @win = TkRoot.new { title 'Funkcje'; minsize(550,600) }
    root = @win
    #canvas
    @canvas = TkCanvas.new(root) do
      place('height' => 500, 'width' => 500, 'x' => 25, 'y' => 75)
    end
    line1 = TkcLine.new( @canvas, 0, 0, 500, 500, :fill => 'red' )
    line2 = TkcLine.new( @canvas, 500, 0, 0, 500, :fill => 'red' )
    line_y = TkcLine.new( @canvas, 250, 0, 250, 500, :fill => 'red' )
    line_x = TkcLine.new( @canvas, 0, 250, 500, 250, :fill => 'red' )
    
    #function menu
    menu = TkMenu.new()
    one = TkMenu.new(menu)
    menu.add('cascade', :menu => one, :label => 'Funkcje')
    one.add('command', :label => 'y = 0', :command => proc { draw(-> (x) { return 0} ) } )
    one.add('command', :label => 'y = x', :command => proc { draw(-> (x) { return x} ) } )
    one.add('command', :label => 'y = x*2', :command => proc { draw(-> (x) { return x*2} ) } )
    one.add('command', :label => 'y = x^2', :command => proc { draw(-> (x) { return x**2} ) } )
    one.add('command', :label => 'y = sin x', :command => proc { draw(-> (x) { return Math.sin(x)} ) } )   
    one.add('command', :label => 'y =  50* sin(x/10)-125', :command => proc { draw(-> (x) { 50* Math.sin(x/10)-125  } ) } )  
    one.add('command', :label => 'y =  250* cos(x/10)', :command => proc { draw(-> (x) { 250* Math.cos(x/10)} ) } )
    one.add('command', :label => 'y =  250* cos(x/100)', :command => proc { draw(-> (x) { 250* Math.cos(x/100)} ) } )
    one.add('command', :label => 'y = log x', :command => proc { draw(-> (x) { if x>=0 then return Math.log(x) else 0 end} ) } )  

    root.menu(menu)
    #range menu
    @entry_from = TkEntry.new(@win) { grid('row'=>1, 'column'=>1) }
    @entry_from.value = "-250"
    @entry_to = TkEntry.new(@win) { grid('row'=>1, 'column'=>2) }
    @entry_to.value = "250"
    @scale = TkEntry.new(@win) { grid('row'=>2, 'column'=>1) }
    @scale.value = "1"
    #opis
    @lb = TkLabel.new(@win){
      text 'Hello World'
      grid('row'=>1, 'column'=>3)
    }
    #TK Loop
    Tk.mainloop
  end

  def wymiary
    @lb.text = "X: od #{@entry_from.value} do #{@entry_to.value}; Y: od #{-250*@scale.value.to_f} do #{250*@scale.value.to_f}"
  end

  def draw(f)
    wymiary
    @canvas.destroy
    @canvas = TkCanvas.new(@win) do
      place('height' => 500, 'width' => 500, 'x' => 25, 'y' => 75)
    end
    $line_x = TkcLine.new( @canvas, 0, 250, 500, 250, :fill => 'red', 'dash' => "-" )
    $line_y = TkcLine.new( @canvas, 250, 0, 250, 500, :fill => 'red', 'dash' => "-" )

    beg = @entry_from.value.to_f
    ending = @entry_to.value.to_f
    skala = @scale.value.to_f
    skok = (beg - ending).abs / 500.00
    puts "Skok: #{skok}, długość: #{(beg - ending).abs}"
    puts "Skala: #{skala}"

    i = 0
    j = 500
    tab = []
    while i <= 500
      wynik = f.call(beg) 
      beg += skok
      tab += [i, 500-(wynik*skala+250)]
      puts "iteracja:#{i}, x:#{beg}, y:#{wynik} | j:#{j}" 
      puts "[#{i}, #{wynik+250}]"
      i += 1
      j -= 1
    end
    line=TkcLine.new( @canvas, tab, :fill => 'black' )
    puts 'Narysowano'
  end
end

x = Okienko.new
x.run