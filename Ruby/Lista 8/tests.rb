require 'open-uri'
require 'nokogiri'
require 'test/unit'
require 'test/unit/ui/console/testrunner'



# Klasa MyHTML działająca na stronach WWW
class MyHTML

    attr_accessor :page_name, :page_content, :indeksy

    # funkcja inicująca podstawową stronę
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
            #print "\n* Aktualnie przeglądamy: "+ start_page + "\n"
            begin
                open(start_page) do | page |
                    if page
                        page = makeString(page)
                        block.call(page)
                        page = Nokogiri::HTML(page).search('body').to_s
                        links = scanLinks(page)
                    end
                end
            rescue OpenURI::HTTPError, SocketError, RuntimeError
                #print "Koniec trasy, link: " + start_page + " jest nieaktywny lub nie działa\n"
            end
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

    # funkcja, która przegląda witryny od podanej strony oraz indeksuje słowa z tej witryny 
    def index(start_page, depth)
        if depth >= 0
            links = []
            #print "\n*Aktualnie przeszukujemy: "+ start_page + "\n"
            begin
                open(start_page) do | page |
                    if page
                        page = makeString(page)
                        page = Nokogiri::HTML(page).search('body')
                        links = scanLinks(page.to_s)
                        page = page.text
                        page.each_line do |line|
                            line = line.downcase.gsub(/[^a-zA-Z0-9\-zżźćńółęąśŻŹĆĄŚĘŁÓŃ_']/, " ") 
                            line = line.split(' ')
                            for e in line
                                if indeksy[e]
                                    indeksy[e] += 1
                                else
                                    indeksy[e] = 1
                                end
                            end
                        end
                    end
                end
            rescue OpenURI::HTTPError, SocketError, RuntimeError
                #print "Koniec trasy przeszukiwania, link: " + start_page + " jest nieaktywny lub nie działa\n"
            end
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
    
    # funkcja wyszukująca słowa pasujące do wyrażenia regularnego 
    def search(reg_exp)
        tab = []
        for word in indeksy
            if reg_exp =~ word[0]
                tab += [word]
            end
        end
        print tab[0..2].to_s + " + #{(tab[0..4].length - 3).to_s} innych wyników"
    end

    # pomocnicza: czyszczenie zindeksowanych słów
    def cleanIndex()
        indeksy={}
    end

    # pomocnicza: stworzenie stringu ze streamu
    def makeString(stream)
        whole = ""
        stream.each_line do | line |
            if line != "\n"
                whole += line
            end
        end
        return whole
    end
    
    # pomocnicza: utworzenie listy linków ze stringu
    def scanLinks(string)
        if string.nil? 
            then return [] end
        return (string.scan(/href\s*=\s*"([^"]*)"/) + string.scan(/href\s*=\s*'([^"]*)'/)).uniq.flatten
    end
end

#########################################################################################

    # oblicza liczbę elementów wpływających na czas ściągania i renderowania strony, takich jak obrazki czy aplety
def page_weight(page)
    images = Nokogiri::HTML(page).search('img').length
    applets = Nokogiri::HTML(page).search('applet').length
    videos = Nokogiri::HTML(page).search('video').length
    audio = Nokogiri::HTML(page).search('audio').length
    sum = (images + applets + videos + audio)
    return "Elementy pobierane: #{sum}\n"
end
    
    # dla każdej strony wypisuje informację o stronie uzyskaną z nagłówka <head>, tj. tytuł, opis, autor, słowa kluczowe etc
def page_summary(page)
    string = ""
    title = Nokogiri::HTML(page).search('title').text.to_s
    string += "Tytuł: #{title} \n"
    description = Nokogiri::HTML(page).search("meta[name='description']").text.to_s
    string += "Opis: #{description} \n"
    author = Nokogiri::HTML(page).search("meta[name='author']").text.to_s
    string += "Autor:  #{author} \n"
    keywords = Nokogiri::HTML(page).search("meta[name='keywords']").text.to_s
    string += "Słowa kluczowe: #{keywords} \n"
    return string
end

#########################################################################################

class TestWeb < Test::Unit::TestCase
    def setup
        @strona = MyHTML.new('http://www.ii.uni.wroc.pl/~marcinm/')
        @page = @strona.page_content
        @indeksy = @strona.indeksy
    end

    def testIndeksyBefore
        raise "This is wrong" unless @indeksy == {}
        raise "This is wrong" unless @indeksy.class == {}.class
    end

    def testBodyString
        assert_instance_of String, @page
        raise "This is wrong" unless @page.class == "".class
    end

    def testWeight
        assert_instance_of String, page_weight(@page)
        raise "This is wrong" unless page_weight(@page).class == "".class
    end

    def testSummary
        assert_instance_of String, page_summary(@page)
        raise "This is wrong" unless page_summary(@page).class == "".class
    end

    def testPrzegladanie
        assert_nothing_raised() { @strona.przeglad('http://www.ii.uni.wroc.pl/~marcinm/', 1, lambda {|page| page_weight(page); page_summary(page)}) }
    end

    def testIndeksowanie
        assert_nothing_raised() { @strona.index('http://www.ii.uni.wroc.pl/~marcinm/', 1) }
    end
end

Test::Unit::UI::Console::TestRunner.run(TestWeb)
x = gets.chomp