import time
import zmq
import sys

def producer(host, port):
	print 'Producer started'
	context = zmq.Context()
	zmq_socket = context.socket(zmq.PUSH)
	zmq_socket.bind("tcp://"+host+":"+port)
	for num in xrange(20000):
		print 'Produced event:[%d]' % (num)
		work_message = { 'num' : num }
		zmq_socket.send_json(work_message)
		time.sleep(2)

if len(sys.argv[1:]) == 1:
	port = sys.argv[1]
	host='*'
elif len(sys.argv[1:]) == 2:
	port = sys.argv[2]
	host = sys.argv[1]
else:
	print 'Invalid port config'
	sys.exit(1)
producer(host,port)
