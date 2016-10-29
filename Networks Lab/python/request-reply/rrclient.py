import zmq
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
print "Connecting to server..."
socket = context.socket(zmq.REQ)
socket.connect (port)
request=0
while True:
    print "Sending request ", request,"..."
    socket.send ("Hello")
    message = socket.recv()
    print "Received reply ", request, "[", message, "]"
    request+=1
