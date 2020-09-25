require 'open-uri'
require 'nokogiri'


class MyHTML

    attr_accessor :page_name, :page_content, :indeksy
    def initialize(page_name)
        @page_name = page_name
        if page_name==''
            @page_content=''
        else
            open(page_name) do | strona |
                @page_content=makeString(strona)
            end   
        end
        @indeksy = {}
    end

    # funkcja ta powinna przeglądać strony serwisu od podanej strony, i dla każdej z nich wykonać instrukcje zawarte w bloku
    def przeglad(start_page, depth, block)
        if depth >= 0
            links = []
            print "\nAktualnie przeglądamy: "+ start_page + "\n"
            print "Głębokość = " + depth.to_s + "\n" 
            begin
                open(start_page) do | page |
                    if page
                        #EVAL/CALL
                        page = makeString(page)
                        #print "\n\nTUTAJ 1\n\n"
                        block.call(page)
                        #print "\n\nTUTAJ 2\n\n"
                        page = Nokogiri::HTML(page).search('body').to_s
                        #page = makeString(page).split("body")[1] #tylko body
                        links = scanLinks(page)
                        #print "Linki: " + links.to_s + "\n"
                    end
                end
            rescue OpenURI::HTTPError, SocketError, RuntimeError
                print "Koniec trasy, link: " + start_page + " jest nieaktywny lub nie działa\n"
            end
            #Kolejne linki
            for link in links
                if (link[0...3] == "www") or (link[0...4] == "http") 
                    przeglad(link, depth - 1, block)
                elsif link[-4..-1] == ".css" or link[-4..-1] == ".ico"
                    next
                elsif link[0] == "#"
                    next
                elsif link[0] == "/"
                    link = start_page + link[1..-1]
                    przeglad(link, depth - 1, block)
                elsif link != start_page
                    if link[-1] != "/" 
                        then link = link + '/' 
                    end
                    link = start_page + link
                    przeglad(link, depth - 1, block)
                end
            end
        end
    end

    # INDEKSOWANIE SŁÓW - tóra przegląda od podanej strony oraz indeksuje słowa ze
    def index(start_page, depth)
        if depth >= 0
            links = []
            print "\nAktualnie przeszukujemy: "+ start_page + "\n"
            print "Głębokość = " + depth.to_s + "\n" 
            begin
                open(start_page) do | page |
                    if page
                        page = makeString(page)
                        page = Nokogiri::HTML(page).search('body')
                        links = scanLinks(page.to_s)
                        #print "Linki: " + links.to_s + "\n"
                        page = page.text
                        page.each_line do |line|
                            line = line.downcase.gsub(/[^a-zA-Z0-9-zżźćńółęąśŻŹĆĄŚĘŁÓŃ_']/, " ") 
                            line = line.split(' ')
                            for e in line
                                if indeksy[e]
                                    indeksy[e] += 1
                                else
                                    indeksy[e] = 1
                                end
                            end
                        end
                        #print indeksy
                    end
                end
            rescue OpenURI::HTTPError, SocketError, RuntimeError
                print "Koniec trasy przeszukiwania, link: " + start_page + " jest nieaktywny lub nie działa\n"
            end
            #Kolejne linki
            for link in links
                if (link[0...3] == "www") or (link[0...4] == "http") 
                    index(link, depth - 1)
                elsif link[-4..-1] == ".css" or link[-4..-1] == ".ico"
                    next
                elsif link[0] == "#"
                    next
                elsif link[0] == "/"
                    link = start_page + link[1..-1]
                    index(link, depth - 1)
                elsif link != start_page
                    if link[-1] != "/" 
                        then link = link + '/' 
                    end
                    link = start_page + link
                    index(link, depth - 1)
                end
            end
        end
    end

    def search(reg_exp)
        tab = []
        for word in indeksy
            if reg_exp =~ word[0]
                tab += [word]
            end
        end
        print tab
    end

    # funkcje pomocnicze
    def cleanIndex()
        indeksy={}
    end
    def makeString(stream)
        #stream = Nokogiri::HTML(stream).to_s
        whole = ""
        stream.each_line do | line |
            if line != "\n"
                whole += line
            end
        end
        return whole
    end
    def scanLinks(string)
        #links_not_parsed = Nokogiri::HTML(string).search('a').to_s
        #print links_not_parsed
        if string.nil? 
            then return [] end
        reg = /href\s*=\s*"([^"]*)"/
        reg2 = /href\s*=\s*'([^"]*)'/
        return (string.scan(reg) + string.scan(reg2)).uniq.flatten
    end
end

#########################################################################################

    # oblicza liczbę elementów wpływających na czas ściągania i renderowania strony, takich jak obrazki czy aplety
def page_weight(page)
    images = Nokogiri::HTML(page).search('img').length
    applets = Nokogiri::HTML(page).search('applet').length
    videos = Nokogiri::HTML(page).search('video').length
    audio = Nokogiri::HTML(page).search('audio').length
    puts images + applets + videos + audio
end
    
    # dla każdej strony wypisuje informację o stronie uzyskaną z nagłówka <head>, tj. tytuł, opis, autor, słowa kluczowe etc
def page_summary(page)
    str = "\n\n" + "#" * 100 + "\n\n"; print str
    reg0 = %r{<title>(.*?)</title>}
    title = Nokogiri::HTML(page).search('title').text.to_s#.split(%r{<title>(.*?)</title>})
    puts "Tytuł: "; puts title
    reg1 = /"description" content\s*=\s*"([^"]*)"/
    reg2 = /"author" content\s*=\s*"([^"]*)"/
    reg3 = /"keywords" content\s*=\s*"([^"]*)"/
    #description = page.scan(reg)
    description = Nokogiri::HTML(page).search("meta[name='description']").to_s.scan(/content\s*=\s*"([^"]*)"/).flatten
    print "\nOpis: \n" ; puts description
    author = Nokogiri::HTML(page).search("meta[name='author']").to_s.scan(/content\s*=\s*"([^"]*)"/).flatten
    print "\nAutor: \n" ; puts author
    keywords = Nokogiri::HTML(page).search("meta[name='keywords']").to_s.scan(/content\s*=\s*"([^"]*)"/).flatten
    print "\nSłowa kluczowe: \n" ; puts keywords
    print str
end

#########################################################################################

strona = MyHTML.new('http://www.ii.uni.wroc.pl/~marcinm/')
strona.przeglad('http://www.ii.uni.wroc.pl/~marcinm/', 1, lambda {|page| page_weight(page); page_summary(page)})
page = strona.page_content
page_summary(page)
page_weight(page)

strona.index('http://www.ii.uni.wroc.pl/~marcinm/', 1)
strona.search(/\d/)