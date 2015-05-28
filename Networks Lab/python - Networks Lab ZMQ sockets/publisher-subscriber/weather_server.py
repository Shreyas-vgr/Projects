import zmq
import random
import sys
import time

if len(sys.argv[1:]) == 1:
    port =  int(sys.argv[1])
else:
	print 'Invalid port config'
	sys.exit(1)

print 'Loading Cities'
cities=[]
with open('in_cities.txt','rb') as f:
	cities = [ line.strip() for line in f]
context = zmq.Context()
socket = context.socket(zmq.PUB)
socket.bind("tcp://*:%s" % port)
while True:
    topic = cities[random.randrange(0,10000)%len(cities)]			#Generate Cities
    messagedata = random.randrange(1,215) - 80						#Generate random temperatures in deg. Farenheit
    print "%s %d" % (topic, messagedata)
    socket.send("%s %d" % (topic, messagedata))
    time.sleep(0.05)
