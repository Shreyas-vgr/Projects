/* if len(sys.argv[1:]) == 1:
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
 */
 <? php 
 $port = $_SERVER['argc'] > 1 ? $_SERVER['argc'][1] : echo "Invalid port config";
 echo "Loading cities";
 $cities =array_combine(range('A','Z'),'');
 $file = fopen("in_cities.txt", "r") or exit("Unable to open file!");
//Output a line of the file until the end is reached
while(!feof($file))
  {		$line = fgets($file);
		$cities[$line[0]]=$cities[$line[0]].$line;
  }
fclose($file);
 echo $cities;

 $context = new ZMQContext();

// Socket to talk to clients
$replier = new ZMQSocket($context, ZMQ::SOCKET_REP);
$replier->bind("tcp://*".":"."$port");

while (true) {
// Wait for next request from client
$request = $responder->recv();
printf ("Received request: [%s]\n", $request);

// Do some 'work'
sleep (1);
if ($cities[$request[0]])
{

// Send reply back to client
$responder->send("ok");
}
else
{
	$responder->send(implode(',',cities[messages[0]]));
}
 
 ?>