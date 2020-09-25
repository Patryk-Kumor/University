require 'drb/drb'
require 'dbm'
require 'time'
require 'yaml'
require 'set'

# The URI for the server to connect to
OUR_URI="druby://localhost:8787"
$database = DBM.open('obiekty') 

# Methods
class MyServer

  def store(obj, id)
    $database[id] = obj.to_yaml
    "Wstawiono"
  end

  def restore(id)
    return YAML.load($database[id]) if $database[id]
  end

  def delete(id)
    $database.delete(id) if $database[id]
  end

  def stan()
    string = "<html>\n<body>\n"
    $database.each { | k, v | string += "\nObiekt o id: #{k}\n => klasy: #{YAML.load(v).class}\n => pola: #{YAML.load(v).inspect    }\n\n" }
    string += "\n</body>"
    return string
  end

  def wyszukaj(lista)
    string = "<html>\n<body>\n"
    for element in $database
      k = element[0]
      v = YAML.load(element[1])
      listaa = Set.new (lista)
      metody = Set.new (v.methods)

      if listaa.subset?(metody)
        string += "\nObiekt o id: #{k}\n => klasy: #{v.class}\n => metody: #{v.methods }\n\n"
      end
    end
    string += "\n</body>"
    return string
  end

end

# The object that handles requests on the server
puts "Zainiciowano serwer " + "druby://localhost:8787"
FRONT_OBJECT=MyServer.new
#$SAFE = 1   # disable eval() and friends
DRb.start_service(OUR_URI, FRONT_OBJECT)
# Wait for the drb server thread to finish before exiting.
DRb.thread.join