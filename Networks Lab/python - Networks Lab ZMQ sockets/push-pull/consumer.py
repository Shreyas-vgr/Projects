import time
import zmq
import random
import sys

def consumer(host, port):
    consumer_id = random.randrange(1,10005)
    print "Consumer #%s demonstrating round-robin packet distribution in ZMQ Push-Pull" % (consumer_id)
    context = zmq.Context()
    # recieve work
    consumer_receiver = context.socket(zmq.PULL)
    consumer_receiver.connect("tcp://"+host+":"+port)
    # send work
    while True:
        work = consumer_receiver.recv_json()
        data = work['num']
        print 'received data with id:[%d]' % (data)

if len(sys.argv[1:]) == 1:
    port = sys.argv[1]
    host='*'
elif len(sys.argv[1:]) == 2:
    port = sys.argv[2]
    host = sys.argv[1]
else:
    print 'Invalid port config'
    sys.exit(1)

consumer(host,port)
