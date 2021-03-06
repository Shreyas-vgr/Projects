import zmq
import time
import sys

if len(sys.argv[1:]) == 1:
    port = sys.argv[1]
    host='*'
elif len(sys.argv[1:]) == 2:
    port = sys.argv[2]
    host = sys.argv[1]
else:
    print 'Invalid port config'
    sys.exit(1)

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://%s:%s" % (host,port))

while True:
    message = socket.recv()
    print "Received request: ", message
    time.sleep (1)  
    socket.send("World from %s" % port)
