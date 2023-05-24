<?php
	$dblink = mysql_connect("localhost","root","123");
	mysql_query("USE chatroom;");
	
	$sql = "SELECT name FROM chatter;";
	$result = mysql_query($sql);

	$response = "";
	while($data = mysql_fetch_array($result)) {
		$response .= "&raquo;&nbsp;{$data['name']}<br>";
	}
	
	mysql_close($dblink);

	header("content-type:text/plain; charset=tis-620");
	echo $response;
?>