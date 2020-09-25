require 'drb/drb'
require 'dbm'
require 'irb'
require 'time'
require 'yaml'

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

x = {}
x["1"] = 1
x["2"] = 2

lista1 = [1,2,3]
lista2 = ["string",2,3]

myserver.store(x, "x")
myserver.store(lista1, "lista1")
myserver.store(lista2, "lista2")

myserver.restore("x")
myserver.restore("lista1")
myserver.restore("lista2")

puts myserver.stan
puts myserver.wyszukaj([:!, :pp, :find, :each_slice])

##############################################################################
#print "--------------------------------------------------------------------\n"
#print "POŁĄCZENIE Z SERWEREM NA PORCIE localhost:8787\n- serwer: myserver\n"
#print "--------------------------------------------------------------------\n"
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