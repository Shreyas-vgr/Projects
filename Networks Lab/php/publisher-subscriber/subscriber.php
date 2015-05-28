
<?php
/*
* Weather update client
* Connects SUB socket to tcp://localhost:5556
* Collects weather updates and finds avg temp in zipcode
* @author Ian Barber <ian(dot)barber(at)gmail(dot)com>
*/

$port = "5556"
if (length($_SERVER['argc']) == 2)
{
	$ports = $_SERVER['argc']['1'];
	$hosts = $_SERVER['argc']['2'];
}
else if (length($_SERVER['argc']) == 4)
{
	$ports = [];
	$hosts =[];
	$ports.append($_SERVER['argc'][1]);
	$ports.append($_SERVER['argc'][3]);
	$hosts.append($_SERVER['argc'][2]);
	$hosts.append($_SERVER['argc'][4]);
}
else
	echo "Invalid port config"
	exit();
/* 	
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
		print '\n'.join(msg.split(',')) */
 
$context = new ZMQContext();
$requester = new ZMQSocket($context, ZMQ::SOCKET_REQ);
$subscriber = new ZMQSocket($context, ZMQ::SOCKET_SUB);
// Socket to talk to server
//echo "Collecting updates from weather server…", PHP_EOL;
$requester->connect("tcp://".$hosts[0].":%s",ports[0]);
$done = 0;
while (!$done)
{	
	$city = $_POST['data'];
	$requester->send($city);
	$msg = $requester->recv();
	if($msg == 'ok')
	{
		$done = 1;
		echo "Collecting updates from weather server...";
		$subscriber->connect("tcp://"."$hosts[1]".":%s",ports[1]);
		$filter = city;
		$subscriber->setSockOpt(ZMQ::SOCKOPT_SUBSCRIBE, $filter);
		$total_temp = 0;
		for ($update_nbr = 0; $update_nbr < 5; $update_nbr++) {
		$string = $subscriber->recv();
		sscanf ($string, "%d %d", $topic, $temperature);
		$total_temp += $temperature;
		
		echo "Average temperature for city '%s' was %dF\n",$filter, (int) ($total_temp / $update_nbr);
	

	}
	else
		echo "City not present in database";
		echo $msg;

}
/* $subscriber->connect("tcp://localhost:5556");

// Subscribe to zipcode, default is NYC, 10001
$filter = $_SERVER['argc'] > 1 ? $_SERVER['argv'][1] : "10002";
$subscriber->setSockOpt(ZMQ::SOCKOPT_SUBSCRIBE, $filter);

// Process 100 updates
$total_temp = 0;
for ($update_nbr = 0; $update_nbr < 100; $update_nbr++) {
$string = $subscriber->recv();
sscanf ($string, "%d %d %d", $zipcode, $temperature, $relhumidity);
$total_temp += $temperature;
}
printf ("Average temperature for zipcode '%s' was %dF\n",
$filter, (int) ($total_temp / $update_nbr));
 */
