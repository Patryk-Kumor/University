require 'drb/drb'
require 'dbm'
require 'irb'
require 'time'

# The URI to connect to
SERVER_URI="druby://localhost:8787"
# Start a local DRbServer to handle callbacks.
#
# Not necessary for this small example, but will be required
# as soon as we pass a non-marshallable object as an argument
# to a dRuby call.
DRb.start_service
myserver = DRbObject.new_with_uri(SERVER_URI)
##############################################################################



puts myserver.get_current_time
#myserver.save('baza', 'Wiadomość 1')
#sleep 1
myserver.save('baza', 'Wiadomość')
puts myserver.show_logs('baza')
puts "\n\n"
puts myserver.raport(Time.parse("2018-12-01 20:00:00 +0100"), Time.now, 'baza', //)


##############################################################################
print "--------------------------------------------------------------------\n"
print "POŁĄCZENIE Z SERWEREM NA PORCIE localhost:8787\n- serwer: myserver\n"
print "--------------------------------------------------------------------\n"
# Wywołanie irb zachowujące lokalne zmienne 
# -> pomocne przy wywoływaniu z konsoli
IRB.setup(nil)
irb = IRB::Irb.new(nil)
IRB.conf[:MAIN_CONTEXT] = irb.context
irb.context.workspace = IRB::WorkSpace.new(binding)
trap 'INT' do
   irb.signal_handle
end
catch(:IRB_EXIT) { irb.eval_input }