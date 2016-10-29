import sys
import zmq

port = "5556"
if len(sys.argv[1:]) == 2:
	ports=map(int,sys.argv[1:])
	hosts= ['localhost']*2

elif len(sys.argv[1:]) == 4:
	ports =  [sys.argv[2],sys.argv[4]]
	hosts =  [sys.argv[1],sys.argv[3]]
else:
	print 'Invalid port config'
	sys.exit(1)
# Socket to talk to server
context = zmq.Context()
socket = context.socket(zmq.SUB)
rsocket = context.socket(zmq.REQ)
rsocket.connect ("tcp://"+hosts[0]+":%s" % ports[0])
done = False
while not done:
	city=raw_input('>Enter the name of the city for weather update subscription:').strip()
	city = city[0].upper()+city[1:]
	rsocket.send(city)
	msg = rsocket.recv()
	if msg=='OK':
		done=True		
		print "Collecting updates from weather server..."
		socket.connect ("tcp://"+hosts[1]+":%s" % ports[1])
		# Subscribe to city
		topicfilter = city
		socket.setsockopt(zmq.SUBSCRIBE, topicfilter)
		# Process 5 updates
		total_value = 0
		for update_nbr in range (5):
			string = socket.recv()
			topic, messagedata = string.split()
			total_value += int(messagedata)
			print topic, messagedata
		print "Average messagedata value for topic '%s' was %dF" % (topicfilter, total_value / update_nbr)
	else:
		print 'City not available in database, other cities that you might be interested in:'
		print '\n'.join(msg.split(','))
