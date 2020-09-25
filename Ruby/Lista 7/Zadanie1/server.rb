require 'drb/drb'
require 'dbm'
require 'time'

# The URI for the server to connect to
OUR_URI="druby://localhost:8787"

# Methods
class MyServer

  def get_current_time
    return Time.now
  end

  def save(prg_id, msg)
    database = DBM.open(prg_id)
    czas = get_current_time.to_s
    database[czas] = msg
    database.close
    return "Pomyślnie zapisano"
  end

  def show_logs(prg_id)
    database = DBM.open(prg_id)
    string = ""
    database.each { | k, v | string += "\nLog z: #{k} => #{v.to_s}" }
    database.close
    return string + "\n\n"
  end

  def raport(from, to, prg_id, re)
    database = DBM.open(prg_id)
    string = ""
    for elem in database
        date = Time.parse(elem[0])
        msg = elem[1]
        if date >= from and date <= to
            string += "\nLog z: #{date} => #{msg}" if re =~ msg
        end
    end
    database.close
    return "<html> <body>" + string + "\n</body>"
  end
end

# The object that handles requests on the server
puts "Zainiciowano serwer " + "druby://localhost:8787"
FRONT_OBJECT=MyServer.new
#$SAFE = 1   # disable eval() and friends
DRb.start_service(OUR_URI, FRONT_OBJECT)
# Wait for the drb server thread to finish before exiting.
DRb.thread.join