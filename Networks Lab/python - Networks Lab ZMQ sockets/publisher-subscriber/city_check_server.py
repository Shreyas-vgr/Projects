import zmq
import time
import sys
import string

if len(sys.argv[1:]) == 1:
    port =  int(sys.argv[1])
else:
	print 'Invalid port config'
	sys.exit(1)

print 'Loading cities'
cities={key: [] for key in list(string.ascii_uppercase)}
with open('in_cities.txt','rb') as f:
	for line in f:
		cities[line[0]].append(line.strip())
print cities
context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:%s" % port)

while True:
    #  Wait for next request from client
    message = socket.recv()
    print "Received request: ", message
    time.sleep(1)
    if message in cities[message[0]]:
    	socket.send("OK")
    else:
    	socket.send(','.join(cities[message[0]]))
