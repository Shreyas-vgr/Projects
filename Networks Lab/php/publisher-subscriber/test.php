<html>
<head></head>
<body>
<h2> Please select a city </h2>
<?php 

	 $file = fopen("in_cities.txt", "r") or exit("Unable to open file!");
	//Output a line of the file until the end is reached
	echo "<form action="client.php" method="POST">"
	while(!feof($file))
	  {		$line = fgets($file);
			
			  echo "<input type="checkbox" name="cities" value=".$line">$line<br>";			  
			  
	  }
	fclose($file);
	echo "<input type="submit" value="Submit">
			</form>"




?>
</body>
</html>
