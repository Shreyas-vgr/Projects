<?php

require_once('connect.php');
session_start();
$ad=$_SESSION['id'];
$allow = array("jpg", "jpeg", "gif", "png");
$name=mysqli_real_escape_string($dbc,$_POST['name']);
$type=mysqli_real_escape_string($dbc,$_POST['ptype']);
$about=mysqli_real_escape_string($dbc,$_POST['about']);
$pic="userpics/page.jpg";
//echo $_FILES['prpic'];
if(!is_uploaded_file($_FILES['prpic']['tmp_name'])) {
   if (!file_exists("user_pics/" . $name.".jpg"))
      { $pic="user_pics/page.jpg";}
	else
	{$pic="user_pics/" . $name.".jpg";}
}
else  // is the file uploaded yet?
{
	$pic="user_pics/" . $name.".jpg";
	$list=explode('.', strtolower( $_FILES['prpic']['name']) );
    $ext = end($list); // whats the extension of the file
    if ( in_array( $ext, $allow) && $_FILES["prpic"]["size"] < 2000000) // is this file allowed
    {
		
        if (file_exists("user_pics/" . $name.".".$ext))
      {
      echo "user_pics/" . $name.".".$ext . " already exists. ";
	  unlink("user_pics/" . $name.".".$ext);
	  move_uploaded_file($_FILES["prpic"]["tmp_name"],
      "user_pics/" . $name.".".$ext);
      }
        else
      {
      move_uploaded_file($_FILES["prpic"]["tmp_name"],
      "user_pics/" . $name.".".$ext);
      echo "Stored in: ";
      }
    }
    else
    {
        // error this file ext is not allowed
    }
}
//Pic upload work done now upload pic link profilepic database
$sql="INSERT INTO prpic (Image_URL) values ('$pic')";
$result = mysqli_query($dbc,$sql) or die('error!!');
$pid = mysqli_insert_id($dbc);
//add user to table
$sql="INSERT INTO page (Admin,Name,Type,PPID,About)
 values ('$ad','$name','$type','$pid','$about')";
 $result = mysqli_query($dbc,$sql) or die('error!!');
 			
			header("Location: http://localhost:8800/Connect+/dashboard.php");
?>