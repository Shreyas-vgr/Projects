
<?php
/*
* Weather update server
* Binds PUB socket to tcp://*:5556
* Publishes random weather updates
* @author Ian Barber <ian(dot)barber(at)gmail(dot)com>
*/
/* if len(sys.argv[1:]) == 1:
    port =  int(sys.argv[1])
else:
	print 'Invalid port config'
	sys.exit(1)
 */
 $port = $_SERVER['argc'] > 1 ? $_SERVER['argc'][1] : echo "Invalid port config";
echo 'Loading Cities'
//print 'Loading Cities'
$cities=[]
/* with open('in_cities.txt','rb') as f:
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
 */

// Prepare our context and publisher
$context = new ZMQContext();
$publisher = $context->getSocket(ZMQ::SOCKET_PUB);
$publisher->bind("tcp://*:%s",$port);

while (true) {
// Get values that will fool the boss
//$zipcode = mt_rand(10000, 10010);
$topic = 
$temperature = mt_rand(1, 215) - 80;
printf("%s %d",$topic,$temperature);
// Send message to all subscribers
$update = sprintf ("%s %d", $topic, $temperature);
$publisher->send($update);
}
